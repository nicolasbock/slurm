#ifndef   _GNU_SOURCE
#  define _GNU_SOURCE
#endif

#ifdef HAVE_CONFIG_H
#  include "config.h"
#  if HAVE_STDINT_H
#    include <stdint.h>
#  endif
#  if HAVE_INTTYPES_H
#    include <inttypes.h>
#  endif
#endif

#include <stdio.h>
#include <stdlib.h>

#include "slurm/slurm.h"
#include "slurm/slurm_errno.h"

#include "src/plugins/select/openstack/select_openstack.h"

#define LOCAL_DEBUG(msg) debug3("%s:%s:%d %s", __FILE__, __func__, __LINE__, msg)

/* These variables are required by the generic plugin interface.  If
 * they are not found in the plugin, the plugin loader will ignore it.
 *
 * plugin_name - a string giving a human-readable description of the
 * plugin.  There is no maximum length, but the symbol must refer to a
 * valid string.
 *
 * plugin_type - a string suggesting the type of the plugin or its
 * applicability to a particular form of data or method of data
 * handling.  If the low-level plugin API is used, the contents of
 * this string are unimportant and may be anything.  SLURM uses the
 * higher-level plugin interface which requires this string to be of
 * the form
 *
 *  <application>/<method>
 *
 * where <application> is a description of the intended application of
 * the plugin (e.g., "select" for SLURM node selection) and <method>
 * is a description of how this plugin satisfies that application.
 * SLURM will only load select plugins if the plugin_type string has a
 * prefix of "select/".
 *
 * plugin_version - an unsigned 32-bit integer containing the Slurm
 * version (major.minor.micro combined into a single number).
 */
const char plugin_name[] = "Linear node selection plugin";
const char plugin_type[] = "select/linear";
const uint32_t plugin_id = 109;
const uint32_t plugin_version = SLURM_VERSION_NUMBER;

/* API Functions

   The following functions must appear. Functions which are not
   implemented should be stubbed.
*/

/* Description:

   Called when the plugin is loaded, before any other functions are
   called. Put global initialization here.

   Returns:

   SLURM_SUCCESS on success, or
   SLURM_ERROR on failure.
*/
int init(void)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Called when the plugin is removed. Clear any allocated storage
   here.

   Returns: None.
*/
void fini(void)
{
        LOCAL_DEBUG("starting");
}

/* STATE SAVE FUNCTIONS
 */

/* Description:

   Save any global node selection state information to a file within
   the specified directory. The actual file name used is plugin
   specific. It is recommended that the global switch state contain a
   magic number for validation purposes. This function is called by
   the slurmctld daemon on shutdown.

   Arguments:

   dir_name (input): fully-qualified pathname of a directory into
   which user SlurmUser (as defined in slurm.conf) can create a file
   and write state information into that file. Cannot be NULL.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
*/
int select_p_state_save(char *dir_name)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Restore any global node selection state information from a file
   within the specified directory. The actual file name used is plugin
   specific. It is recommended that any magic number associated with
   the global switch state be verified. This function is called by the
   slurmctld daemon on startup.

   Arguments:

   dir_name (input) fully-qualified pathname of a directory containing
   a state information file from which user SlurmUser (as defined in
   slurm.conf) can read. Cannot be NULL.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR, causing slurmctld to exit.
*/
int select_p_state_restore(char *dir_name)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* STATE INITIALIZATION FUNCTIONS
 */

/* Description:

   Note the initialization of the node record data structure. This
   function is called by the slurmctld daemon when the node records
   are initially established and again when any nodes are added to or
   removed from the data structure.

   Arguments:

   node_ptr (input) pointer to the node data records. Data in these
   records can read. Nodes deleted after initialization may have their
   the name field in the record cleared (zero length) rather than
   rebuilding the node records and bitmaps.

   node_cnt (input) number of node data records.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR, causing slurmctld to exit.
*/
int select_p_node_init(struct node_record *node_ptr, int node_cnt)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Note the initialization of the partition record data
   structure. This function is called by the slurmctld daemon when the
   partition records are initially established and again when any
   partition configurations change.

   Arguments:

   part_list (input) list of partition record entries. Note that some
   of these partitions may have no associated nodes. Also consider
   that nodes can be removed from one partition and added to a
   different partition.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR, causing slurmctld to exit.
 */
int select_p_block_init(List block_list)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Used at slurmctld daemon startup to synchronize plugin (and node)
   state with that of currently active jobs.

   Arguments:

   job_list (input) list of slurm jobs from slurmctld job records.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
*/
int select_p_job_init(List job_list_arg)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Used to notify plugin of change in partition configuration or
   general configuration change. The plugin will test global variables
   for changes as appropriate.

   Returns:

   SLURM_SUCCESS if successful, otherwise SLURM_ERROR.
 */
int select_p_reconfigure(void)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* NODE-SPECIFIC FUNCTIONS
 */

/* Description:

   Allocate a buffer for select plugin specific information about a
   node. Use select_p_select_nodeinfo_free() to free the returned data
   structure.

   Returns:

   A buffer for select plugin specific information about a node or
   NULL on failure. Use select_p_select_nodeinfo_free() to free this
   data structure.
 */
select_nodeinfo_t *select_p_select_nodeinfo_alloc(void)
{
        LOCAL_DEBUG("starting");
        select_nodeinfo_t *nodeinfo = NULL;
        return nodeinfo;
}

/* Description:

   Pack select plugin specific information about a node into a buffer
   for node queries.

   Argument:

   nodeinfo (input) Node information to be packed.

   buffer (input/output) pointer to buffer into which the node
   information is packed.

   protocol_version (input) Version number of the data packing
   mechanism (needed for backward compatibility).

   Returns:

   SLURM_SUCCESS if successful, otherwise SLURM_ERROR
*/
int select_p_select_nodeinfo_pack(select_nodeinfo_t * nodeinfo, Buf buffer,
                                  uint16_t protocol_version)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Unpack select plugin specific information about a node from a
   buffer for node queries. Use select_p_select_nodeinfo_free() to
   free the returned data structure.

   Argument:

   nodeinfo (output) Node information unpacked from the buffer. Use
   select_p_select_nodeinfo_free() to free the returned data
   structure.

   buffer (input/output) pointer to buffer from which the node
   information is to be unpacked.

   protocol_version (input) Version number of the data packing
   mechanism (needed for backward compatibility).

   Returns:

   SLURM_SUCCESS if successful, otherwise SLURM_ERROR
 */
int select_p_select_nodeinfo_unpack(select_nodeinfo_t ** nodeinfo, Buf buffer,
                                    uint16_t protocol_version)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Free a buffer which was previously allocated for select plugin
   specific information about a node.

   Argument:

   nodeinfo (input/output) The buffer to be freed.

   Returns:

   SLURM_SUCCESS if successful, otherwise SLURM_ERROR
 */
int select_p_select_nodeinfo_free(select_nodeinfo_t * nodeinfo)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Reset select plugin specific information about a job. Called by
   slurmctld daemon after that job's state has been restored (at
   startup) or job has been scheduled.

   Argument:

   job_ptr (input) Pointer to the updated job.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
*/
int select_p_select_nodeinfo_set(struct job_record *job_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Update select plugin specific information about every node as
   needed.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
*/
int select_p_select_nodeinfo_set_all(void)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Get information from a select plugin's node specific data
   structure.

   Argument:

   nodeinfo (input) Node information data structure from which
   information is to get retrieved.

   dinfo (input) Data type to be retrieved.

   state (input) Node state filter to be applied (e.g. only get
   information about ALLOCATED nodes).

   data (output) The retrieved data.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
*/
int select_p_select_nodeinfo_get(select_nodeinfo_t * nodeinfo,
                                 enum select_nodedata_type dinfo,
                                 enum node_states state, void *data)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   note that a node has registered with a different configuration than
   previously registered. For example, the node was configured with
   1GB of memory in slurm.conf, but actually registered with 2GB of
   memory.

   Arguments:

   index (input) zero origin index of the node in reference to the
   entire system.

   Returns:

   SLURM_SUCCESS if successful, otherwise SLURM_ERROR
*/
int select_p_update_node_config(int index)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   This function is called by the slurmctld daemon at start time to
   set node rank information for recording the nodes to optimize
   application performance.

   Arguments:

   node_ptr (input/output) pointer to the node data structure. Each
   node's node rank field may be set.

   node_cnt (input) number of nodes configured on the system.

   Returns:

   true if node rank information has been set.
*/
bool select_p_node_ranking(struct node_record * node_ptr, int node_cnt)
{
        LOCAL_DEBUG("starting");
        return true;
}

/* Description:

   push a node state change into the plugin. The index should be the
   index from the slurmctld of the entire system.

   Arguments:

   node_ptr (input/output) pointer to the node data structure. Each
   node's node rank field may be set.

   Returns:

   SLURM_SUCCESS if successful, otherwise SLURM_ERROR
*/
int select_p_update_node_state(struct node_record *node_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Used for systems like an IBM Bluegene system where one Slurm node
   is mapped to many compute nodes. In Bluegene's case one Slurm
   node/midplane represents 512 compute nodes, but since 512 is
   typically the smallest allocatable block Slurm treats it as one
   node. This is a function so the user can issue a 'real' number and
   the function will alter it so Slurm can understand what the user
   really means in Slurm terms.

   Arguments:

   type (input) enum telling the plugin how to transform the data.

   data (input/output) Is a void * and the actual data type depends
   upon the first argument to this function (type).

   Returns:

   SLURM_SUCCESS if successful, otherwise SLURM_ERROR
*/
int select_p_alter_node_cnt(enum select_node_cnt type, void *data)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* BLOCK-SPECIFIC FUNCTIONS
 */

/* Description:

   Update the state of a portion of a Slurm node. Currently used on
   BlueGene systems to place node cards within a midplane into or out
   of an error state.

   Arguments:

   block_desc_ptr (input) pointer to the modified block containing the
   sub-block name and its new state.

   Returns:

   SLURM_SUCCESS if successful, otherwise SLURM_ERROR
*/
int select_p_update_sub_node(update_block_msg_t * block_desc_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   This function is called when the admin needs to manually update the
   state of a block.

   Arguments:

   block_desc_ptr (input) block description variable. Containing the
   block name and the state to set the block.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
*/
int select_p_update_block(update_block_msg_t * block_desc_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* JOB-SPECIFIC FUNCTIONS
 */

/* Description:

   Allocate a buffer for select plugin specific information about a
   job. Use select_p_select_jobinfo_free() to free the allocated
   memory.

   Returns:

   Pointer to a select plugin buffer for a job or NULL on failure. Use
   select_p_select_jobinfo_free() to free the allocated memory.
 */
select_jobinfo_t *select_p_select_jobinfo_alloc(void)
{
        select_jobinfo_t *jobinfo = NULL;
        LOCAL_DEBUG("starting");
        return jobinfo;
}

/* Description:

   Copy the buffer containing select plugin specific information about
   a job. Use select_p_select_jobinfo_free() to free the allocated
   memory.

   Arguments:

   jobinfo (input) pointer to the select plugin specific information
   about a job.

   Returns:

   A copy of jobinfo or NULL on failure. Use
   select_p_select_jobinfo_free() to free the allocated memory.
 */
select_jobinfo_t *select_p_select_jobinfo_copy(select_jobinfo_t * jobinfo)
{
        LOCAL_DEBUG("starting");
        return NULL;
}

/* Description:

   Free the buffer containing select plugin specific information about
   a job.

   Arguments:

   jobinfo (input) pointer to the select plugin specific information
   about a job.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
 */
int select_p_select_jobinfo_free(select_jobinfo_t * jobinfo)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Pack into a buffer the contents of the select plugin specific
   information about a job.

   Arguments:

   jobinfo (input) pointer to the select plugin specific information
   about a job.

   buffer (input/output) pointer to buffer into which the job
   information is packed.

   protocol_version (input) Version number of the data packing
   mechanism (needed for backward compatibility).

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
 */
int select_p_select_jobinfo_pack(select_jobinfo_t * jobinfo, Buf buffer,
                                 uint16_t protocol_version)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Unpack from a buffer the contents of the select plugin specific
   information about a job. The returned value must be freed using
   select_p_select_jobinfo_free().

   Arguments:

   jobinfo (output) pointer to the select plugin specific information
   about a job. The returned value must be freed using
   select_p_select_jobinfo_free().

   buffer (input/output) pointer to buffer from which the job
   information is unpacked.

   protocol_version (input) Version number of the data packing
   mechanism (needed for backward compatibility).

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
 */
int select_p_select_jobinfo_unpack(select_jobinfo_t ** jobinfo_pptr, Buf buffer,
                                   uint16_t protocol_version)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Get the contents of a field from the select plugin specific
   information about a job.

   Arguments:

   jobinfo (input) pointer to the select plugin specific information
   about a job to be read.

   data_type (input) identification of the field to be retrieved.

   data (output) data read from the job record.

   Returns: SLURM_SUCCESS if successful. On failure, the plugin should
   return SLURM_ERROR.
 */
int select_p_select_jobinfo_get(select_jobinfo_t * jobinfo,
                                enum select_jobdata_type data_type, void *data)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Set a field in the select plugin specific information about a job.

   Arguments:

   jobinfo (input/output) pointer to the select plugin specific
   information about a job to be modified.

   data_type (input) identification of the field to be set.

   data (input) data to be written into the job record.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
 */
int select_p_select_jobinfo_set(select_jobinfo_t * jobinfo,
                                enum select_jobdata_type data_type, void *data)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Print the contents of the select plugin specific information about
   a job.

   Arguments:

   jobinfo (input) pointer to the select plugin specific information
   about a job.

   buf (input/output) buffer into which the contents are written.

   size (input) size of buf in bytes.

   mode (input) print mode, see enum select_print_mode.

   Returns:

   Pointer to the buf on success or NULL on failure.
 */
char *select_p_select_jobinfo_sprint(select_jobinfo_t * jobinfo, char *buf,
                                     size_t size, int mode)
{
        LOCAL_DEBUG("starting");
        return buf;
}

/* Description:

   Print the contents of the select plugin specific information about
   a job. The return value must be released using the xfree()
   function.

   Arguments:

   jobinfo (input) pointer to the select plugin specific information
   about a job.

   mode (input) print mode, see enum select_print_mode.

   Returns:

   Pointer to a string on success or NULL on failure. Call xfree() to
   release the memory allocated for the return value.
 */
char *select_p_select_jobinfo_xstrdup(select_jobinfo_t * jobinfo, int mode)
{
        LOCAL_DEBUG("starting");
        return NULL;
}

/* Description:

   Given a job's scheduling requirement specification and a set of
   nodes which might be used to satisfy the request, identify the
   nodes which "best" satisfy the request. Note that nodes being
   considered for allocation to the job may include nodes already
   allocated to other jobs, even if node sharing is not
   permitted. This is done to ascertain whether or not job may be
   allocated resources at some later time (when the other jobs
   complete). This permits Slurm to reject non-runnable jobs at submit
   time rather than after they have spent hours queued. Informing
   users of problems at job submission time permits them to quickly
   resubmit the job with appropriate constraints.

   Arguments:

   job_ptr (input) pointer to the job being considered for
   scheduling. Data in this job record may safely be read. Data of
   particular interest include details->contiguous (set if allocated
   nodes should be contiguous), num_procs (minimum processors in
   allocation) and details->req_node_bitmap (specific required nodes).

   bitmap (input/output) bits representing nodes which might be
   allocated to the job are set on input. This function should clear
   the bits representing nodes not required to satisfy job's
   scheduling request. Bits left set will represent nodes to be used
   for this job. Note that the job's required nodes
   (details->req_node_bitmap) will be a superset bitmap when the
   function is called.

   min_nodes (input) minimum number of nodes to allocate to this
   job. Note this reflects both job and partition specifications.

   max_nodes (input) maximum number of nodes to allocate to this
   job. Note this reflects both job and partition specifications.

   req_nodes (input) the requested (desired) of nodes to allocate to
   this job. This reflects job's maximum node specification (if
   supplied).

   mode (input) controls the mode of operation. Valid options are:
   * SELECT_MODE_RUN_NOW: try to schedule job now
   * SELECT_MODE_TEST_ONLY: test if job can ever run
   * SELECT_MODE_WILL_RUN: determine when and where job can run

   preemption_candidates (input) list of pointers to jobs which may be
   preempted in order to initiate this pending job. May be NULL if
   there are no preemption candidates.

   preempted_jobs (input/output) list of jobs which must be preempted
   in order to initiate the pending job. If the value is NULL, no job
   list is returned. If the list pointed to has a value of NULL, a new
   list will be created otherwise the existing list will be
   overwritten. Use the list_destroy function to destroy the list when
   no longer needed.

   exc_core_bitmap (input) bitmap of cores held for advanced
   reservations.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR .
 */
int select_p_job_test(struct job_record *job_ptr, bitstr_t * bitmap,
                      uint32_t min_nodes, uint32_t max_nodes,
                      uint32_t req_nodes, uint32_t mode,
                      List preemption_candidates, List * preempted_jobs,
                      bitstr_t * exc_core_bitmap)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Note the initiation of the specified job is about to begin. This
   function is called immediately after select_p_job_test()
   successfully completes for this job.

   Arguments:

   job_ptr (input) pointer to the job being initialized. Data in this
   job record may safely be read or written. The nodes and node_bitmap
   fields of this job record identify the nodes which have already
   been selected for this job to use.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR, which causes the job to be requeued for later
   execution.
 */
int select_p_job_begin(struct job_record *job_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Test if resources are configured and ready for job execution. This
   function is only used in the job prolog for BlueGene systems to
   determine if the bgblock has been booted and is ready for use.

   Arguments:

   job_ptr (input) pointer to the job being initialized. Data in this
   job record may safely be read. The nodes and node_bitmap fields of
   this job record identify the nodes which have already been selected
   for this job to use.

   Returns:

   1 if the job may begin execution, 0 otherwise.
 */
int select_p_job_ready(struct job_record *job_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Note the termination of the specified job. This function is called
   as the termination process for the job begins (prior to killing the
   tasks).

   Arguments:

   job_ptr (input) pointer to the job being terminated. Data in this
   job record may safely be read or written. The nodes and/or
   node_bitmap fields of this job record identify the nodes which were
   selected for this job to use.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
 */
int select_p_job_fini(struct job_record *job_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Signal the specified job. This is needed for architectures where
   the job steps are launched by a mechanism outside of Slurm, for
   example when ALPS is used on Cray systems.

   Arguments:

   job_ptr (input) pointer to the job to be signaled.

   signal (input) signal to be sent to the job.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return a
   Slurm error code.
 */
int select_p_job_signal(struct job_record *job_ptr, int signal)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Confirm that a job's memory allocation is still valid after a node
   is restarted. This is an issue if the job is allocated all of the
   memory on a node and that node is restarted with a different memory
   size than at the time it is allocated to the job. This would mostly
   be an issue on an Intel KNL node where the memory size would vary
   with the MCDRAM cache mode.

   Arguments:

   job_ptr (input) pointer to the job to be validated.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return a
   Slurm error code.
 */
int select_p_job_mem_confirm(struct job_record *job_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Suspend the specified job. Release resources for use by other jobs.

   Arguments:

   job_ptr (input) pointer to the job being suspended. Data in this
   job record may safely be read or written. The nodes and/or
   node_bitmap fields of this job record identify the nodes which were
   selected for this job to use.

   indf_susp (input) flag which if set indicates the job is being
   suspended indefinitely by the user or administrator. If not set,
   the job is being suspended temporarily for gang scheduling.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return a
   Slurm error code.
 */
int select_p_job_suspend(struct job_record *job_ptr, bool indf_susp)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Resume the specified job which was previously suspended.

   Arguments:

   job_ptr (input) pointer to the job being resumed. Data in this job
   record may safely be read or written. The nodes and/or node_bitmap
   fields of this job record identify the nodes which were selected
   for this job to use.

   indf_susp (input) flag which if set indicates the job is being
   resumed after being suspended indefinitely by the user or
   administrator. If not set, the job is being resumed after being
   temporarily suspended for gang scheduling.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return a
   Slurm error code.
 */
int select_p_job_resume(struct job_record *job_ptr, bool indf_susp)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Report the ability of this select plugin to expand jobs.

   Returns:

   True if job expansion is supported, otherwise false.
 */
int select_p_job_expand_allow(void)
{
        LOCAL_DEBUG("starting");
        return false;
}

/* Description:

   Transfer all resources currently allocated to one job to another
   job. One job is left with no allocated resources and the other job
   is left with the resources previously allocated to both jobs.

   Arguments:

   from_job_ptr (input) pointer to the job being to have all of its
   resources removed.

   to_job_ptr (input) pointer to the job getting all of the resources
   previously either job.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return a
   Slurm error code.
 */
int select_p_job_expand(struct job_record *from_job_ptr,
                        struct job_record *to_job_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Remove the specified node from the job's allocation.

   Arguments:

   job_ptr (input) pointer to the job being decreased in size.

   node_ptr (input) pointer to the node being removed from a job's
   allocation.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return a
   Slurm error code.
 */
int select_p_job_resized(struct job_record *job_ptr,
                         struct node_record *node_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* STEP-SPECIFIC FUNCTIONS
 */

/* Description:

   If the select plugin needs to select nodes for a job step, then do
   so here.  NOTE: Only select/bluegene selects the job step
   resources. The logic within the slurmctld daemon directly selects
   resources for a job step for all other select plugins.

   Arguments:

   job_ptr (input) Pointer to the job which is attempting to allocate
   a job step.

   step_jobinfo (input/output) On input, this is a pointer to an empty
   buffer. On output for a successful job step allocation, this
   structure is filled in with detailed information about the job step
   allocation.

   node_count (input) Number of nodes required by the new job step.

   Returns:

   If successful, then return a bitmap of the nodes allocated to the
   job step, otherwise return NULL and the logic within the slurmctld
   daemon will select the nodes to be allocated to the job step.
 */
bitstr_t *select_p_step_pick_nodes(struct job_record *job_ptr,
                                   select_jobinfo_t * step_jobinfo,
                                   uint32_t node_count)
{
  bitstr_t *bitmap = NULL;
	LOCAL_DEBUG("starting");
        return bitmap;
}

/* Description:

   Note that a job step is completing execution

   Arguments:

   step_ptr (input) Pointer to the step which has completed execution.

   killing_step (input) True if we are begining the termination of the
   step (for example, when SIGKILL is being sent); False if the
   termination of the step has completed (all processes have exited).

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
 */
int select_p_step_finish(struct step_record *step_ptr, bool killing_step)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   This function fails certain cnodes in a blocks midplane.

   Arguments:

   step_ptr (input) information on the step that has failed cnodes.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
 */
int select_p_fail_cnode(struct step_record *step_ptr)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* ADVANCED RESERVATION FUNCTIONS
 */

/* Description:

   Identify the nodes which best satisfy a reservation request taking
   system topology into consideration if applicable.

   Arguments:

   resv_desc_ptr (input/output) the request of the reservation. The
   node_list could be changed inside of the plugin.

   node_cnt (input) number of nodes required to satisfy the
   reservation request.

   avail_bitmap (input/output) a bitmap of the nodes which are
   available for use in creating the reservation.

   core_bitmap (input/output) cores which can not be used for this
   reservation IN, and cores to be used in the reservation OUT (flush
   bitstr then apply only used cores).

   Returns:

   A bitmap of the nodes which should be used for the advanced
   reservation or NULL if the selected nodes can not be used for an
   advanced reservation.
 */
bitstr_t *select_p_resv_test(resv_desc_msg_t * resv_desc_ptr, uint32_t node_cnt,
                             bitstr_t * avail_bitmap, bitstr_t ** core_bitmap)
{
  bitstr_t *bitmap = NULL;
        LOCAL_DEBUG("starting");
        return bitmap;
}

/* GET INFORMATION FUNCTIONS
 */

/* Description:

   Get plugin-specific information about a job.

   Arguments:

   info (input) identifies the type of data to be updated.

   job_ptr (input) pointer to the job related to the query (if
   applicable; may be NULL).

   data (output) the requested data.

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
 */
int select_p_get_info_from_plugin(enum select_plugindata_info dinfo,
                                  struct job_record *job_ptr, void *data)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* Description:

   Pack plugin-specific information about its general state into a
   buffer. Currently only used by select/bluegene to pack block state
   information.

   NOTE: Functions to work with this data may be needed on computers
   without the plugin which generated the data, so those functions are
   in src/common modules. The unpack function is performed by
   slurm_unpack_block_info_members() in
   src/common/slurm_protocol_pack.c using BlueGene specific data
   structures. Use destroy_select_ba_request() in
   src/common/noe_select.c to free the data structure's memory.

   Arguments:

   last_query_time (input) Time when the data was previously requested
   (used so only updated information needs to be sent).

   show_flags (input) identifies the type of data requested.

   buffer_ptr (input/output) Pointer to buffer filled in with select
   plugin state information.

   protocol_version (input) Version number of the data packing
   mechanism (needed for backward compatibility).

   Returns:

   SLURM_SUCCESS if successful. On failure, the plugin should return
   SLURM_ERROR.
 */
int select_p_pack_select_info(time_t last_query_time, uint16_t show_flags,
                              Buf * buffer_ptr, uint16_t protocol_version)
{
        LOCAL_DEBUG("starting");
        return SLURM_SUCCESS;
}

/* BLOCK ALLOCATOR INTERFACE
 */

/* Description:

   Construct an internal block allocation table containing information
   about the nodes on a computer. This allocated memory should be
   released by calling select_p_ba_fini();

   Arguments:

   node_info_ptr (input) Information about the nodes on a system.

   sanity_check (input) if set then validate that the node name suffix
   values represent coordinates which are within the system's
   dimension size (see function select_p_ba_get_dims).
 */
void select_p_ba_init(node_info_msg_t * node_info_ptr, bool sanity_check)
{
        LOCAL_DEBUG("starting");
}

/* Description:

   Free storage allocated by select_p_ba_init().
 */
void select_p_ba_fini(void)
{
        LOCAL_DEBUG("starting");
}

/* Description:

   Return an array containing the number of elements in each dimension
   of the system size. For example, an IBM Bluegene/P system has a
   three-dimensional torus topology. If it has eight elements in the X
   dimension, and four in the Y and Z dimensions, the returned array
   will contain the values 8, 4, 4.

   Returns:

   An array containing the number of elements in each dimension of the
   system size.
 */
int *select_p_ba_get_dims(void)
{
  int *dimensions = NULL;
        LOCAL_DEBUG("starting");
        return dimensions;
}

/* Description:

   Returns a bitmap representing the cnodelist input with the bits of
   the cnodelist in a midplane not set.

   Arguments:

   cnodelist (input) cnodelist (e.g. on a BGQ it would look something
   like '[00000x11331]').

   Returns:

   A bitmap the size of the number of cnodes in a midplane with the
   bits available for use unset.
 */
bitstr_t *select_g_ba_cnodelist2bitmap(char *cnodelist)
{
  bitstr_t *bitmap = NULL;
        LOCAL_DEBUG("starting");
        return bitmap;
}

int select_p_step_start(struct step_record *step_ptr)
{
        LOCAL_DEBUG("starting");
	return SLURM_SUCCESS;
}

bitstr_t *select_p_ba_cnodelist2bitmap(char *cnodelist)
{
        LOCAL_DEBUG("starting");
	return NULL;
}
