# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/leo/.espressif/v6.1/esp-idf/components/bootloader/subproject"
  "/home/leo/dvmt/esp_c_three_minione_projects/gpio_button_led/build/bootloader"
  "/home/leo/dvmt/esp_c_three_minione_projects/gpio_button_led/build/bootloader-prefix"
  "/home/leo/dvmt/esp_c_three_minione_projects/gpio_button_led/build/bootloader-prefix/tmp"
  "/home/leo/dvmt/esp_c_three_minione_projects/gpio_button_led/build/bootloader-prefix/src/bootloader-stamp"
  "/home/leo/dvmt/esp_c_three_minione_projects/gpio_button_led/build/bootloader-prefix/src"
  "/home/leo/dvmt/esp_c_three_minione_projects/gpio_button_led/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/leo/dvmt/esp_c_three_minione_projects/gpio_button_led/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/leo/dvmt/esp_c_three_minione_projects/gpio_button_led/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
