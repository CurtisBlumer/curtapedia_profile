;;;
;; Copyright (C) 2014 Curtis Blumer
;;
;; This program is free software; you can redistribute it and/or
;; modify it under the terms of the GNU General Public License
;; as published by the Free Software Foundation; either version 2
;; of the License, or (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
;; Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
;;;

api = 2
core = 7.x

;; Download newest Drupal release and the Responsive Bartik theme

;projects[] = "drupal"
projects[responsive_bartik][version] = "1"

;;;
;; Custom modules
;;;

; Get Curtapedia Drupal 8 enhancements dependencies

projects[curtapedia_profile_d8][type] = "module"
projects[curtapedia_profile_d8][subdir] = "custom"
projects[curtapedia_profile_d8][download][type] = "git"
projects[curtapedia_profile_d8][download][url] = "file:///home/cblumer/Development/curtapedia_d8/.git"
projects[curtapedia_profile_d8][download][branch] = "7.x-1.x"

; Download installation profile locally
;projects[curtapedia_security][type] = "module"
;projects[curtapedia_security][download][type] = "git"
;projects[curtapedia_security][download][url] = "file:///home/cblumer/Development/curtapedia_security/.git"
;projects[curtapedia_security][download][branch] = "7.x-1.x"

; Download installation profile for GitHub
;projects[curtapedia_security][type] = "module"
;projects[curtapedia_security][download][type] = "git"
;projects[curtapedia_security][download][url] = "https://github.com/cblumer88/curtapedia_security.git"
;projects[curtapedia_security][download][branch] = "master"

;;;
;; Contributed modules
;;;

;; Viniculum 1.x allows for Trackbacks and Pingbacks
;; Patches clean up code and add support for Rules
;projects[viniculum][type] = "module"
;projects[viniculum][subdir] = "patched"
;projects[viniculum][download][url] = "https://git.drupal.org/project/vinculum.git"
;projects[viniculum][download][branch] = "7.x-1.x"
;projects[viniculum][download][revision] = "a91754ad118504f414d2fcc54315830845475666"
;projects[viniculum][patch][] = "https://www.drupal.org/files/issues/continue-queue_0.patch"
;projects[viniculum][patch][] = "https://www.drupal.org/files/vinculum_rules_0.patch"

;; Viniculum 2.x allows for Trackbacks, Pingbacks, and WebMentions ;;
projects[viniculum][type] = "module"
projects[viniculum][download][url] = "https://github.com/sanduhrs/vinculum.git"
projects[viniculum][download][branch] = "7.x-2.x"
projects[viniculum][download][revision] = "a91754ad118504f414d2fcc54315830845475666"
projects[viniculum][subdir] = "contrib-git"


;; Essentials modules

projects[autosave][version] = "1"
projects[autosave][subdir] = "contrib"

projects[globalredirect][version] = "1"
projects[globalredirect][subdir] = "contrib"

projects[libraries][version] = "2"
projects[libraries][subdir] = "contrib"

projects[pathauto][version] = "2"
projects[pathauto][subdir] = "contrib"

projects[redirect][version] = "1"
projects[redirect][subdir] = "contrib"

projects[token][version] = "1"
projects[token][subdir] = "contrib"

projects[transliteration][version] = "3"
projects[transliteration][subdir] = "contrib"


;; Media modules
;;
;; These simplify the current mess that is Drupal media management

projects[colorbox][version] = "2"
projects[colorbox][subdir] = "contrib"

projects[file_entity][version] = "2"
projects[file_entity][subdir] = "contrib"

projects[media][version] = "2.0-alpha4"
projects[media][subdir] = "contrib"

projects[mediaelement][version] = "1"
projects[mediaelement][subdir] = "contrib"

projects[media_colorbox][version] = "1"
projects[media_colorbox][subdir] = "contrib"

projects[plupload][version] = "1"
projects[plupload][subdir] = "contrib"


;; User experience (UX) modules
;;
;; These are useful in easing the users experience while using Drupal.

projects[logintoboggan][version] = "1"
projects[logintoboggan][subdir] = "contrib"

projects[password_tab][version] = "1"
projects[password_tab][subdir] = "contrib"


;; Administrator experience (AX) modules
;;
;; Modules that help sie administrators manage users more effectively.

projects[email_confirm][version] = "1"
projects[email_confirm][subdir] = "contrib"

projects[email_registration][version] = "1"
projects[email_registration][subdir] = "contrib"