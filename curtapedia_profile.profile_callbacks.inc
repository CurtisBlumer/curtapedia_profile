<?php
/*
 * @file
 * Callbacks used when installing the profile.
 * 
 * @author cblumer88
 * @copyright (c) 2014, Curtis Blumer
 * @version 7.x-1.x-dev
 */

/**
 * BatchAPI callback.
 *
 * @see curtapedia_profile_install_additional_modules()
 */
function _curtapedia_profile_enable_module($module, $module_name, &$context) {
  module_enable(array($module), FALSE);
  $context['message'] = st('Installed %module module.', array('%module' => $module_name));
}

function _curtapedia_profile_flush_caches($operation, &$context) {
  $context['message'] = t('@operation', array('@operation' => $operation));
  drupal_flush_all_caches();
}