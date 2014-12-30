<?php
/**
 * Callbacks used when installing the profile
 * 
 * @author cblumer88
 * @copyright 2014 Curtis Blumer
 * @license http://www.gnu.org/licenses/gpl-3.0.html
 * @version 1.0
 */

/**
 * BatchAPI callback.
 *
 * @param object $module Module object.
 * @param string $module_name Module name.
 * @param object $context The Batch API context.
 * 
 * @see curtapedia_profile_install_additional_modules()
 * 
 * @return void
 */
function _curtapedia_profile_enable_module($module, $module_name, &$context) {
  $context['message'] = t('Installing %module module.', array('%module' => $module_name));
  module_enable(array($module), FALSE);
}
/**
 * Simple cache clearing helper function.
 * 
 * This function only exists so that it may report back to the Batch API.
 * 
 * @param string $operation Text used to explain what is happeneing.
 * @param object $context The Batch API context.
 * 
 * @return void 
 */
function _curtapedia_profile_flush_caches(&$context) {
  $context['message'] = t("Flushing website caches.");
  drupal_flush_all_caches();
}