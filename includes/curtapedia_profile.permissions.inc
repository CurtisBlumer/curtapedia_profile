<?php

/* 
 * Copyright (C) 2014 cblumer
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

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
function _curtapedia_profile_user_settings_install_adminin_role() {
  $admin_role['role'] = new stdClass();
  $admin_role['role']->name = 'Super administrator';
  $admin_role['role']->weight = 50;
  $admin_role['permissions'] = array_keys(module_invoke_all('permission'));
  
  user_role_save($admin_role['role']);
  user_role_grant_permissions($admin_role['role']->rid, $admin_role['permissions']);

  //Assign User 1 the Drupal Administrator Role.
  db_insert('users_roles')->fields(
    array(
      'uid' => 1,
      'rid' => $admin_role['role']->rid,
    )
  )->execute();
  
  // Set the role in the Variables table
  variable_set('user_admin_role', $admin_role['role']->rid);
}

/* Define other Drupal user roles
 * 
 * Defines other Drupal 7 roles that parity WordPress roles. Roles must be 
 * defined after all the content types are created so that permssions may be 
 * properly assigned for them. This should be called last.
 * 
 * @return array
 * 
 * @todo Move permission configuration into install task.
*/
function _curtapedia_profile_user_roles_define() {
  $user_roles['site administrator']['role'] = new stdClass();
  $user_roles['site administrator']['role']->name = 'Site Administrator';
  $user_roles['site administrator']['role']->weight = 49;
  $user_roles['site administrator']['permissions'] = array(
    'administer blocks',
    'access content',
    //'access navbar',
    'access content overview',
    'administer nodes',
    'view own unpublished content',
    'view revisions',
    'revert revisions',
    'delete revisions',
    'administer themes',
    'access administration pages',
    'access site in maintenance mode',
    'access user profiles',
  );
  
  $user_roles['editor']['role'] = new stdClass();
  $user_roles['editor']['role']->name = 'Editor';
  $user_roles['editor']['role']->weight = 48;
  $user_roles['editor']['permissions'] = array(
    'access content',
    //'access navbar',
    'access content overview',
    'view own unpublished content',
    'view revisions',
    'revert revisions',
    'create page content',
    'edit any page content',
    'access user profiles',
  );

  $user_roles['author']['role'] = new stdClass();
  $user_roles['author']['role']->name = 'Author';
  $user_roles['author']['role']->weight = 47;
  $user_roles['author']['permissions'] = array(
    'access content',
    //'access navbar',
    'access content overview',
    'view own unpublished content',
    'view revisions',
    'create own page content',
    'edit own page content',
    'access user profiles',
  );

  $user_roles['contributor']['role'] = new stdClass();
  $user_roles['contributor']['role']->name = 'Contributor';
  $user_roles['contributor']['role']->weight = 46;
  $user_roles['contributor']['permissions'] = array(
    'access content',
    'view own unpublished content',
    'view revisions',
    'create own page content',
    'edit own page content',
    'access user profiles',
  );

  foreach($user_roles as $user_role) {
    user_role_save($user_role['role']);
    user_role_grant_permissions($user_role['role']->rid, $user_role['permissions']);
  }
}

/*
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
  if(is_string($drupal_role) && is_int($role_weight)) {
    $role = new stdClass();
    $role->name = $drupal_role;
    $role->weight = $role_weight;
    user_role_save($role);
    $context['message'] = t('Created the @role role.', array('@role' => $drupal_role));
    
    if(is_object($role) && is_callable('_curtapedia_profile_user_settings_install_permissions')) {
      $role_permissions = _curtapedia_profile_user_settings_permissions_define($role);
      user_role_grant_permissions($role->rid, $role_permissions);
      $context['message'] = t('Granted permissions for the @role role.', array('@role' => $drupal_role));
    }
  }
}

function _curtapedia_profile_user_settings_roles_define() {
  $roles[] = "Administrator";
  $roles[] = "Editor";
  $roles[] = "Author";
  $roles[] = "Contributor";
  return $roles;
}

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
  } else {
    return FALSE;
  }
}
function _curtapedia_profile_user_settings_flush_caches($operation, &$context) {
  $context['message'] = t('Flushed all caches.');
  drupal_flush_all_caches();
}