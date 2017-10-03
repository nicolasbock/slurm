# Makefile for select/openstack plugin

AUTOMAKE_OPTIONS = foreign

PLUGIN_FLAGS = -module -avoid-version --export-dynamic

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/src/common

pkglib_LTLIBRARIES = select_openstack.la

# openstack job resource selection plugin.
select_openstack_la_SOURCES = select_openstack.c select_openstack.h
select_openstack_la_LDFLAGS = $(SO_LDFLAGS) $(PLUGIN_FLAGS)
