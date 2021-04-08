/*
   Copyright (c) 2020, The LineageOS Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/system_properties.h>
#include <sys/_system_properties.h>

#include "vendor_init.h"

using android::base::GetProperty;
using android::base::SetProperty;

void property_override(char const prop[], char const value[]) {
  prop_info *pi;

  pi = (prop_info *)__system_property_find(prop);
  if (pi)
    __system_property_update(pi, value, strlen(value));
  else
    __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_dalvikvm_properties() {
  struct sysinfo sys;
  sysinfo(&sys);
  if (sys.totalram > 8192ull * 1024 * 1024) {
    // from - phone-xhdpi-12288-dalvik-heap.mk
    property_override("dalvik.vm.heapstartsize", "24m");
    property_override("dalvik.vm.heapgrowthlimit", "384m");
    property_override("dalvik.vm.heaptargetutilization", "0.42");
    property_override("dalvik.vm.heapmaxfree", "56m");
    }
  else if(sys.totalram > 6144ull * 1024 * 1024) {
    // from - phone-xhdpi-8192-dalvik-heap.mk
    property_override("dalvik.vm.heapstartsize", "24m");
    property_override("dalvik.vm.heapgrowthlimit", "256m");
    property_override("dalvik.vm.heaptargetutilization", "0.46");
    property_override("dalvik.vm.heapmaxfree", "48m");
    }
  else {
    // from - phone-xhdpi-6144-dalvik-heap.mk
    property_override("dalvik.vm.heapstartsize", "16m");
    property_override("dalvik.vm.heapgrowthlimit", "256m");
    property_override("dalvik.vm.heaptargetutilization", "0.5");
    property_override("dalvik.vm.heapmaxfree", "32m");
  }
  property_override("dalvik.vm.heapsize", "512m");
  property_override("dalvik.vm.heapminfree", "8m");
}

void load_op7(const char *model) {
  property_override("ro.product.model", model);
  property_override("ro.product.name", "OnePlus7");
  property_override("ro.build.product", "OnePlus7");
  property_override("ro.product.device", "OnePlus7");
  property_override("ro.vendor.product.device", "OnePlus7");
  property_override("ro.display.series", "OnePlus 7");
}

void load_op7pro(const char *model) {
  property_override("ro.product.model", model);
  property_override("ro.product.name", "OnePlus7Pro");
  property_override("ro.build.product", "OnePlus7Pro");
  property_override("ro.product.device", "OnePlus7Pro");
  property_override("ro.vendor.product.device", "OnePlus7Pro");
  property_override("ro.display.series", "OnePlus 7 Pro");
}

void load_op7t(const char *model) {
  property_override("ro.product.model", model);
  property_override("ro.product.name", "OnePlus7T");
  property_override("ro.build.product", "OnePlus7T");
  property_override("ro.product.device", "OnePlus7T");
  property_override("ro.vendor.product.device", "OnePlus7T");
  property_override("ro.display.series", "OnePlus 7T");
}

void load_op7tpro(const char *model) {
  property_override("ro.product.model", model);
  property_override("ro.product.name", "OnePlus7TPro");
  property_override("ro.build.product", "OnePlus7TPro");
  property_override("ro.product.device", "OnePlus7TPro");
  property_override("ro.vendor.product.device", "OnePlus7TPro");
  property_override("ro.display.series", "OnePlus 7T Pro");
}

void vendor_load_properties() {
  int project_name = stoi(android::base::GetProperty("ro.boot.project_name", ""));
  int rf_version = stoi(android::base::GetProperty("ro.boot.rf_version", ""));
  switch(project_name){
    case 18857:
      switch (rf_version){
        case 1:
          /* China*/
          load_op7("GM1900");
          break;
        case 3:
          /* India*/
          load_op7("GM1901");
          break;
        case 4:
          /* Europe */
          load_op7("GM1903");
          break;
        case 5:
          /* Global / US Unlocked */
          load_op7("GM1907");
          break;
        default:
          /* Generic */
          load_op7("GM1907");
          break;
      }
      break;
    case 18821:
      switch (rf_version){
        case 1:
          /* China*/
          load_op7pro("GM1910");
          break;
        case 3:
          /* India*/
          load_op7pro("GM1911");
          break;
        case 4:
          /* Europe */
          load_op7pro("GM1913");
          break;
        case 5:
          /* Global / US Unlocked */
          load_op7pro("GM1917");
          break;
        default:
          /* Generic*/
          load_op7pro("GM1917");
          break;
      }
      break;
    case 18865:
      switch (rf_version){
        case 1:
          /* China*/
          load_op7t("HD1900");
          break;
        case 3:
          /* India*/
          load_op7t("HD1901");
          break;
        case 4:
          /* Europe */
          load_op7t("HD1903");
          break;
        case 5:
          /* Global / US Unlocked */
          load_op7t("HD1907");
          break;
        default:
          /* Generic */
          load_op7t("HD1907");
          break;
      }
      break;
      case 19801:
      switch (rf_version){
        case 1:
          /* China*/
          load_op7tpro("HD1910");
          break;
        case 3:
          /* India*/
          load_op7tpro("HD1911");
          break;
        case 4:
          /* Europe */
          load_op7tpro("HD1913");
          break;
        case 5:
          /* Global / US Unlocked */
          load_op7tpro("HD1917");
          break;
        default:
          /* Generic*/
          load_op7tpro("HD1917");
          break;
      }
      break;
  }

  // dalvikvm props
  load_dalvikvm_properties();

}
