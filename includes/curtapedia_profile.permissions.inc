<?php
/**
 * Defines and configures default user settings
 * 
 * Defines and configures default user roles and permissions as well as provides
 * callbacks for Batch API for installation tasking.
 * 
 * @author cblumer88
 * @copyright 2014 Curtis Blumer
 * @license http://www.gnu.org/licenses/gpl-3.0.html
 * @version 1.0
 */

/**
 * @var string SUPER_ADMIN_ROLE Drupal 'Site administrtor' role.
 */
define('SUPER_ADMIN_ROLE', 'Super administrator');

/**
 * @var string SLEP_TIME This is or testing.
 */
define('SLEEP_TIMER', 2);

/** 
 * Define default Drupal user roles
 * 
 * Defines default Drupal 7 roles that parity WordPress roles. Roles must be 
 * defined after all modules are enabled oo that permssions may be assigned once.
 * 
 * @var array $roles is an array of pre-defined Drupal roles.  
 * 
 * @return string[] Array of pre-defined roles.
 */
function _curtapedia_profile_user_settings_roles_define() {
  $roles[] = "Administrator";
  $roles[] = "Editor";
  $roles[] = "Author";
  $roles[] = "Contributor";
  return $roles;
}

/** 
 * Define default Drupal role permission
 * 
 * Defines default Drupal 7 roles permissions that parity WordPress roles.
 * Permissions must be defined after all modules are enabled and roles are
 * installed so that permssions may be assigned only once.
 * 
 * @param string $role_name is the name of a Drupal role
 * 
 * @var array $permissions is an array of pre-defined Drupal permissions per role.  
 * 
 * @return string[] Array of pre-defined permissions.
 */
function _curtapedia_profile_user_settings_permissions_define($role_name = NULL) {
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
 * @param string $role_name The name of the Drupal role.
 * @param int $role_weight The weight of the Drupal role; larger weights sink, smaller weights float.
 * @param object $context The Batch API context.
 * 
 * @uses user_role_grant_permissions() To set permissions in the database.
 * 
 * @return void
 */
function _curtapedia_profile_user_settings_role_save($role_name = NULL, $role_weight = NULL, &$context) {
  // Type checking parameters; PHP doesn't have full type hinting.
  if(is_string($role_name) && is_int($role_weight)) {
    $role = new stdClass();
    $role->name = $role_name;
    $role->weight = $role_weight;
    user_role_save($role);
    $context['message'] = t('Created the @role role.', array('@role' => $role_name));
    sleep(SLEEP_TIMER);
    
    $role_permissions = _curtapedia_profile_user_settings_permissions_define($role_name);
    user_role_grant_permissions($role->rid, $role_permissions);
    foreach($role_permissions as $permission) {
      $context['message'] = t('Granted @permission to @role role.', array('@permission' => $permission, '@role' => $role_name));
      sleep(SLEEP_TIMER);
    }
    $context['message'] = t('Granted permissions for the @role role.', array('@role' => $role_name));
    sleep(SLEEP_TIMER);
  } else {
    if(!is_string($role_name)) {
      $replacements = array(
        '@function' => __FUNCTION__,
        '@param_name'=> '$role_name',
        '@param_value' => $role_name,
        '@param_type_needed' => 'string',
        '@param_type_passed' => gettype($role_name),
      );
      drupal_set_message(t("@function parameter @param_name must be passed a @param_type_needed, it was passed: (@param_type_passed) @param_value", $replacements), 'error');
    }
    if(!is_int($role_weight)) {
      $replacements = array(
        '@function' => __FUNCTION__,
        '@param_name'=> '$role_weight',
        '@param_value' => $role_weight,
        '@param_type_needed' => 'integer',
        '@param_type_passed' => gettype($role_weight),
      );
      drupal_set_message(t("@function parameter @param_name must be passed a @param_type_needed, it was passed: (@param_type_passed) @param_value", $replacements), 'error');
    }
  }
}

/**
 * Save Drupal Role into the database
 * 
 * Creates a stdClass() object and uses passed information to install a role's
 * permissions as defined by _curtapedia_profile_user_settings_install_permissions().
 * 
 * @param int $user_id The User ID of the user being added to a Role.
 * @param int $role_id The Role ID of that Role.
 * @param object $context The Batch API context
 * 
 * @uses db_insert() Inserts data into the database
 * @uses drupal_set_message() To report erros in type hinting.
 * 
 * @return void 
 */
function _curtapedia_profile_user_settings_role_add_user($user_id = NULL, $role_id = NULL, &$context) {
  if(is_int($user_id) & is_int($role_id)) {
    $query = db_insert('users_roles')
      ->fields(
        array(
          'uid' => $user_id,
          'rid' => $role_id,
        )
      )->execute();
    
    $user_object = user_load($user_id);
    $user_name = $user_object->name;
    
    $role_object = user_role_load($role_id);
    $role_name = $role_object->name;
    
    $context['message'] = t('Assigned @user the @role role.', array('@user'=> $user_name, '@role' => $role_name));
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
      drupal_set_message(t("@function parameter @param_name must be passed a @param_type_needed, it was passed: (@param_type_passed) @param_value", $replacements), 'error');
    }
    if(!is_int($role_id)) {
      $replacements = array(
        '@function' => __FUNCTION__,
        '@param_name'=> '$role_id',
        '@param_value' => $role_id,
        '@param_type_needed' => 'integer',
        '@param_type_passed' => gettype($role_id),
      );
      drupal_set_message(t("@function parameter @param_name must be passed a @param_type_needed, it was passed: (@param_type_passed) @param_value", $replacements), 'error');
    }
  }
}

/**
 * Define the Drupal Site Administrator role.
 * 
 * In Drupal the the Administrator Role is a bit of a misnomer given the average
 * site admin should not be able to access some of Drupal's advanced settings.
 * This should be called before '_curtapedia_profile_user_roles_define()'.
 * 
 * @param object $context The Batch API context
 * 
 * @uses _curtapedia_profile_user_settings_role_add_user() to add users to roles.
 * 
 * @return void
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
  $context['message'] = t('Created @role role.', array('@role' => SUPER_ADMIN_ROLE));
  sleep(SLEEP_TIMER);

  // Set the 'Super administrator' as the admin role in the {variables} table
  variable_set('user_admin_role', $role_id);

  // Grant 'Super administrator' role all permissions.
  $role_permissions = array_keys(module_invoke_all('permission'));
  user_role_grant_permissions($role_id, $role_permissions);
  
  // Notify Batch API of progress (this is for the end user).
  $context['message'] = t('Granted all permissions to @role role.', array('@role' => SUPER_ADMIN_ROLE));
  sleep(SLEEP_TIMER);

  // Add Drupal super user (UID: 1) to 'Super administrator' role.
  _curtapedia_profile_user_settings_role_add_user(1, $role_id, $context);
}

/**
 * Simple cache clearing helper function.
 * 
 * This function only exists so that it may report back to the Batch API.
 * 
 * @param string $operation
 * @param object $context The Batch API context
 * 
 * @return void 
 */
function _curtapedia_profile_user_settings_flush_cache($operation, &$context) {
  $context['message'] = t('@operation', array('@operation' => $operation));
  drupal_flush_all_caches();
}