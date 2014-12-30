<?php

define('SUPER_ADMIN_ROLE', 'Super administrator');

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
function _curtapedia_profile_user_settings_permissions_define($drupal_role) {
  if(is_string($drupal_role)) {
    switch ($drupal_role) {
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
 * @param string $drupal_role The name of the Drupal role
 * @param int $role_weight The weight of the Drupal role; larger weights sink, smaller weights float.
 * 
 * @return bool
 */
function _curtapedia_profile_user_settings_role_save($drupal_role, $role_weight = 0, &$context) {
  drupal_set_message(__FUNCTION__ . '::$drupal_role = ' . '(' . gettype($drupal_role) . ')' . $drupal_role, 'info', FALSE);
  drupal_set_message(__FUNCTION__ . '::$role_weight = ' . '(' . gettype($role_weight) . ')' . $role_weight, 'info', FALSE);
  //if(is_string($drupal_role) && is_int($role_weight)) {
    $role = new stdClass();
    $role->name = $drupal_role;
    $role->weight = $role_weight;
    user_role_save($role);
    $context['message'] = st('Created the @role role.', array('@role' => $drupal_role));
    
    if(function_exists('_curtapedia_profile_user_settings_install_permissions')) {
      $role_permissions = _curtapedia_profile_user_settings_permissions_define($role);
      user_role_grant_permissions($role->rid, $role_permissions);
      $context['message'] = st('Granted permissions for the @role role.', array('@role' => $drupal_role));
    } else {
      drupal_set_message("Function: '_curtapedia_profile_user_settings_permissions_define' does not exist",  'info');
    }
  //}
}

function _curtapedia_profile_user_settings_role_add_user($user_id = NULL, $role_id = NULL, &$context) {
  drupal_set_message(__FUNCTION__ . '::$user_id = ' . '(' . gettype($user_id) . ')' . $user_id, 'info', FALSE);
  drupal_set_message(__FUNCTION__ . '::$role_id = ' . '(' . gettype($role_id) . ')' . $role_id, 'info', FALSE);
  //if(is_int($user_id) & is_int($role_id)) {
    $query = db_insert('users_roles')
      ->fields(
        array(
          'uid' => $user_id,
          'rid' => $role_id,
        )
      )->execute();
    if(is_int($query)) {
      $user_object = user_load($user_id);
      $role_object = user_role_load($role_id);
      $context['message'] = st('Assigned @user the @role role.', array('@user'=> $user_object->name, '@role' => $role_object->name));
    }
  //}
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
  settype($role_id, "integar");
  
  // Notify Batch API of progess (this is for the end user).
  $context['message'] = st('Created the @role role.', array('@role' => SUPER_ADMIN_ROLE));

  // Set the 'Super administrator' as the admin role in the {variables} table
  variable_set('user_admin_role', $role_id);

  // Grant 'Super administrator' role all permissions.
  $role_permissions = array_keys(module_invoke_all('permission'));
  user_role_grant_permissions($role_id, $role_permissions);
  
  // Notify Batch API of progress (this is for the end user).
  $context['message'] = st('Granted all permissions for the @role role.', array('@role' => SUPER_ADMIN_ROLE));

  // Add Drupal super user (UID: 1) to 'Super administrator' role.
  _curtapedia_profile_user_settings_role_add_user(1, $role_id);
}

/*
 * Simple cache clearing helping function.
 * 
 * This function only exists so that it may report back to the Batch API.
 */
function _curtapedia_profile_flush_caches($operation, &$context) {
  drupal_flush_all_caches();
  $context['message'] = st('@operation', array('@operation' => $operation));
}