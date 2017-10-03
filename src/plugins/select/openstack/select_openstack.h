#ifndef _SELECT_OPENSTACK_H
#define _SELECT_OPENSTACK_H
#include "src/common/slurm_topology.h"
#include "src/slurmctld/slurmctld.h"

/* part_cr_record keeps track of the number of running jobs on this node in
 * this partition. SLURM allows a node to be assigned to more than one
 * partition. One or more partitions may be configured to share the cores with
 * more than one job.
 */

struct part_cr_record {
        struct part_record *part_ptr;   /* pointer to partition in slurmctld */
        uint16_t run_job_cnt;   /* number of running jobs on this node
                                 * for this partition */
        uint16_t tot_job_cnt;   /* number of jobs allocated to this
                                 * node for this partition (RUNNING &
                                 * SUSPENDED) */
        struct part_cr_record *next;    /* ptr to next part_cr_record */
};

/*
 * node_cr_record keeps track of the resources within a node which
 * have been reserved by already scheduled jobs.
 */
struct node_cr_record {
        struct part_cr_record *parts;   /* ptr to singly-linked part_cr_record
                                         * list that contains alloc_core info */
        uint32_t alloc_memory;  /* real memory reserved by already
                                 * scheduled jobs */
        uint16_t exclusive_cnt; /* count of jobs exclusively allocated
                                 * this node (from different partitions) */
        List gres_list;         /* list of gres state info managed by 
                                 * plugins */
};

struct cr_record {
        struct node_cr_record *nodes;   /* ptr to array of node records */
        uint32_t *run_job_ids;  /* job IDs for running jobs */
        uint16_t run_job_len;   /* length of run_job_ids array */
        uint32_t *tot_job_ids;  /* job IDs for allocated jobs 
                                 * (RUNNING & SUSPENDED)*/
        uint16_t tot_job_len;   /* length of tot_job_ids array */
};

#endif
