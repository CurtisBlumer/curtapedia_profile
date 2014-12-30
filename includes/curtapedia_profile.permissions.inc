<?php

define('SUPER_ADMIN_ROLE', 'Super administrator');
define('SLEEP_TIMER', 0.75);

/** 
 * Define Drupal user roles
 * 
 * Defines default Drupal 7 roles that parity WordPress roles. Roles must be 
 * defined after all modules are enabled oo that permssions may be assigned once.
 * 
 * @return array
 */
function _curtapedia_profile_user_settings_roles_define() {
  $roles[] = "Administrator";
  $roles[] = "Editor";
  $roles[] = "Author";
  $roles[] = "Contributor";
  return $roles;
}

/** 
 * Define Drupal user permissions
 * 
 * @return array
 */
function _curtapedia_profile_user_settings_permissions_define($role_name) {
  if(is_string($role_name)) {
    switch ($role_name) {
      case 'Contributor':
        $permissions[] = 'access content';
        $permissions[] = 'view own unpublished content';
        $permissions[] = 'view revisions';
        $permissions[] = 'create page content';
        $permissions[] = 'edit own page content';
        $permissions[] = 'access user profiles';
        break;
      case 'Author':
        $permissions[] = 'access navbar';
        $permissions[] = 'access content';
        $permissions[] = 'access content overview';
        $permissions[] = 'view own unpublished content';
        $permissions[] = 'view revisions';
        $permissions[] = 'create page content';
        $permissions[] = 'edit own page content';
        $permissions[] = 'access user profiles';
        break;
      case 'Editor':
        $permissions[] = 'access navbar';
        $permissions[] = 'access content';
        $permissions[] = 'access content overview';
        $permissions[] = 'view own unpublished content';
        $permissions[] = 'view revisions';
        $permissions[] = 'revert revisions';
        $permissions[] = 'create page content';
        $permissions[] = 'edit any page content';
        $permissions[] = 'access user profiles';
        break;
      case 'Administrator':
        $permissions[] = 'administer blocks';
        $permissions[] = 'view revisions';
        $permissions[] = 'revert revisions';
        $permissions[] = 'delete revisions';
        $permissions[] = 'create page content';
        $permissions[] = 'edit any page content';
        $permissions[] = 'delete any page content';
        $permissions[] = 'access user profiles';
        $permissions[] = 'administer themes';
        $permissions[] = 'access administration pages';
        $permissions[] = 'access site in maintenance mode';
        break;
    }
    return $permissions;
  }
}

/**
 * Save Drupal Role into the database
 * 
 * Creates a stdClass() object and uses passed information to install a role's
 * permissions as defined by _curtapedia_profile_user_settings_install_permissions().
 * 
 * @param string $role_name The name of the Drupal role
 * @param int $role_weight The weight of the Drupal role; larger weights sink, smaller weights float.
 * 
 * @return bool
 */
function _curtapedia_profile_user_settings_role_save($role_name, $role_weight = 0, &$context) {
  // Type checking parameters because PHP doesn't have type hinting.
  if(is_string($role_name) && is_int($role_weight)) {
    $role = new stdClass();
    $role->name = $role_name;
    $role->weight = $role_weight;
    user_role_save($role);
    $context['message'] = st('Created the @role role.', array('@role' => $role_name));
    sleep(SLEEP_TIMER);
    
    $role_permissions = _curtapedia_profile_user_settings_permissions_define($role_name);
    user_role_grant_permissions($role->rid, $role_permissions);
    $context['message'] = st('Granted permissions for the @role role.', array('@role' => $role_name));
    sleep(SLEEP_TIMER);;
  } else {
    if(!is_string($role_name)) {
      $replacements = array(
        '@function' => __FUNCTION__,
        '@param_name'=> '$role_name',
        '@param_value' => $role_name,
        '@param_type_needed' => 'string',
        '@param_type_passed' => gettype($role_name),
      );
      drupal_set_message(st("@function parameter @param_name must be passed a @param_type_needed, it was passed: (@param_type_passed) @param_value", $replacements), 'error');
    }
    if(!is_int($role_weight)) {
      $replacements = array(
        '@function' => __FUNCTION__,
        '@param_name'=> '$role_weight',
        '@param_value' => $role_weight,
        '@param_type_needed' => 'integer',
        '@param_type_passed' => gettype($role_weight),
      );
      drupal_set_message(st("@function parameter @param_name must be passed a @param_type_needed, it was passed: (@param_type_passed) @param_value", $replacements), 'error');
    }
  }
}

function _curtapedia_profile_user_settings_role_add_user($user_id, $role_id, &$context) {
  if(is_int($user_id) & is_int($role_id)) {
    $query = db_insert('users_roles')
      ->fields(
        array(
          'uid' => $user_id,
          'rid' => $role_id,
        )
      )->execute();
    $user_object = user_load($user_id);
    $replacements = array(
      '@open_tags' => "<pre><code>",
      '@close_tags' => "</code></pre>",
      '@var_dump' => var_dump($user_object),
    );
    drupal_set_message(st("@open_tags @var_dump @close_tags", $replacements), "info", TRUE);
    $role_object = user_role_load($role_id);
    $replacements = array(
      '@open_tags' => "<pre><code>",
      '@close_tags' => "</code></pre>",
      '@var_dump' => var_dump($role_object),
    );
    drupal_set_message(st("@open_tags @var_dump @close_tags", $replacements), "info", TRUE);
    $context['message'] = st('Assigned @user the @role role.', array('@user'=> $user_object->name, '@role' => $role_object->name));
    sleep(SLEEP_TIMER);
  } else {
    if(!is_int($user_id)) {
      $replacements = array(
        '@function' => __FUNCTION__,
        '@param_name'=> '$user_id',
        '@param_value' => $user_id,
        '@param_type_needed' => 'string',
        '@param_type_passed' => gettype($user_id),
      );
      drupal_set_message(st("@function parameter @param_name must be passed a @param_type_needed, it was passed: (@param_type_passed) @param_value", $replacements), 'error');
    }
    if(!is_int($role_id)) {
      $replacements = array(
        '@function' => __FUNCTION__,
        '@param_name'=> '$role_id',
        '@param_value' => $role_id,
        '@param_type_needed' => 'integer',
        '@param_type_passed' => gettype($role_id),
      );
      drupal_set_message(st("@function parameter @param_name must be passed a @param_type_needed, it was passed: (@param_type_passed) @param_value", $replacements), 'error');
    }
  }
}

/*
 * Define the Drupal Site Administrator role.
 * 
 * In Drupal the the Administrator Role is a bit of a misnomer given the average
 * site admin should not be able to access some of Drupal's advanced settings.
 * This should be called before '_curtapedia_profile_user_roles_define()'.
 * 
 * @return array
 * 
 * @todo Move permission configuration into install task.
*/
function _curtapedia_profile_user_settings_role_admin_create(&$context) {
  // Instantiate a new role object.
  $role = new stdClass();
  $role->name = SUPER_ADMIN_ROLE;
  $role->weight = 50;
  
  // Save role object to database and get role ID.
  user_role_save($role);  
  $role_id = $role->rid;
  
  // Set $role_id to integar to ensure functionality.
  // Other custom functions have conditionals to ensure data consistency.
  settype($role_id, "integer");
  
  // Notify Batch API of progess (this is for the end user).
  $context['message'] = st('Created @role role.', array('@role' => SUPER_ADMIN_ROLE));
  sleep(SLEEP_TIMER);;

  // Set the 'Super administrator' as the admin role in the {variables} table
  variable_set('user_admin_role', $role_id);

  // Grant 'Super administrator' role all permissions.
  $role_permissions = array_keys(module_invoke_all('permission'));
  user_role_grant_permissions($role_id, $role_permissions);
  
  // Notify Batch API of progress (this is for the end user).
  $context['message'] = st('Granted all permissions to @role role.', array('@role' => SUPER_ADMIN_ROLE));
  sleep(SLEEP_TIMER);;

  // Add Drupal super user (UID: 1) to 'Super administrator' role.
  _curtapedia_profile_user_settings_role_add_user(1, $role_id);
}

/*
 * Simple cache clearing helping function.
 * 
 * This function only exists so that it may report back to the Batch API.
 */
function _curtapedia_profile_flush_caches($operation, &$context) {
  $context['message'] = st('@operation', array('@operation' => $operation));
  drupal_flush_all_caches();
}