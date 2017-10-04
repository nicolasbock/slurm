#!/bin/bash

set -u
set -e

scriptdir=$(readlink -f $(dirname $0))
basedir=$(readlink -f "${scriptdir}"/..)
: ${install_directory:=/usr/local/slurm}
: ${slurm_version:=16-05-8-1}
: ${slurm_dir:="${basedir}"/slurm-slurm-${slurm_version}}
: ${slurm_plugin_dir:="${install_directory}"/lib/slurm}

unpack_slurm_source() {
    pushd "${basedir}"
    wget --timestamping \
        https://github.com/SchedMD/slurm/archive/slurm-${slurm_version}.tar.gz
    tar xf slurm-${slurm_version}.tar.gz || exit
    popd
}

configure_slurm() {
    pushd "${basedir}"/slurm-slurm-${slurm_version}
    ./configure \
        --runstatedir="${install_directory}/run" \
        --prefix="${install_directory}" || exit
    popd
}

build_slurm() {
    pushd "${basedir}"/slurm-slurm-${slurm_version}
    make -j3 || exit
    popd
}

setup_slurm_user() {
    groupadd slurm || true
    useradd \
        --home-dir "${install_directory}" \
        --gid slurm \
        slurm || true
}

install_slurm() {
    [[ -d "${install_directory}" ]] && rm -rf "${install_directory}"
    pushd "${slurm_dir}"
    make install || exit
    popd
}

fixup_slurm_conf() {
    mkdir -p "${install_directory}"/{etc,log,var}
    sed -e "s:linux0:$(hostname -s):" \
        -e "s:^SlurmctldDebug=.*:SlurmctldDebug=debug3:" \
        -e "s:^SlurmdDebug=.*:SlurmdDebug=debug3:" \
        -e "s:^SelectType=.*:SelectType=select/openstack:" \
        -e "s:^[#]*SlurmctldLogFile=.*:SlurmctldLogFile=${install_directory}/log/slurmctld.log:" \
        -e "s:^[#]*SlurmdLogFile=.*:SlurmdLogFile=${install_directory}/log/slurmd.log:" \
        slurm.conf.example > "${install_directory}"/etc/slurm.conf || exit
    cat "${install_directory}"/etc/slurm.conf
}

fixup_directories() {
    chown -R root:root "${install_directory}"
    chown -R slurm:slurm "${install_directory}"/log
    chown -R slurm:slurm "${install_directory}"/var
}

start_slurm() {
    [[ -f /var/run/slurmctld.pid ]] && kill -HUP $(cat /var/run/slurmctld.pid)
    [[ -f /var/run/slurmd.pid ]] && kill -HUP $(cat /var/run/slurmd.pid)
    "${install_directory}"/sbin/slurmctld || exit
    "${install_directory}"/sbin/slurmd || exit
}

dump_logs() {
    cat /var/log/munge/*.log
    cat "${install_directory}"/log/slurmctld.log
    cat "${install_directory}"/log/slurmd.log
}

configure_plugin() {
    autoreconf --force --install
    ./configure --disable-static \
        --prefix="${install_directory}" \
        --with-slurm-dir="${slurm_dir}" \
        --with-slurm-plugin-dir="${slurm_plugin_dir}" \
        CPPFLAGS=-I"${install_directory}"/include\ -DDEBUG \
        CFLAGS="-g3 -O0 --coverage" \
        LDFLAGS="--coverage"
}

build_plugin() {
    make -j3
}

install_plugin() {
    make install
}

usage() {
    cat <<EOF
Usage: $(basename ${0}) [--debug] COMMAND [COMMAND [...]]

--debug     Print a lot of extra information

Known commands:

unpack_slurm_source
configure_slurm
build_slurm
setup_slurm_user
install_slurm
fixup_slurm_conf
fixup_directories
start_slurm
dump_logs
configure_plugin
build_plugin
install_plugin
usage
EOF
}

if [[ $# -gt 0 && $1 == "--debug" ]]; then
    set -x
    PS4='+(${BASH_SOURCE##*/}:${LINENO}) ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'
    shift
fi

if (( $# == 0 )); then
    usage
    exit 0
fi

while (( $# > 0 )); do
    echo "executing ${1}"
    $1
    shift
done
