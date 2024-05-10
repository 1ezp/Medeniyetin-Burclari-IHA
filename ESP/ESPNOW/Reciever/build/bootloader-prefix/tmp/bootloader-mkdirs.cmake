# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/diamond/.platformio/lib/esp-idf/components/bootloader/subproject"
  "/home/diamond/Desktop/Github/Medeniyetin-Burclari-IHA/ESP/ESPNOW/Reciever/build/bootloader"
  "/home/diamond/Desktop/Github/Medeniyetin-Burclari-IHA/ESP/ESPNOW/Reciever/build/bootloader-prefix"
  "/home/diamond/Desktop/Github/Medeniyetin-Burclari-IHA/ESP/ESPNOW/Reciever/build/bootloader-prefix/tmp"
  "/home/diamond/Desktop/Github/Medeniyetin-Burclari-IHA/ESP/ESPNOW/Reciever/build/bootloader-prefix/src/bootloader-stamp"
  "/home/diamond/Desktop/Github/Medeniyetin-Burclari-IHA/ESP/ESPNOW/Reciever/build/bootloader-prefix/src"
  "/home/diamond/Desktop/Github/Medeniyetin-Burclari-IHA/ESP/ESPNOW/Reciever/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/diamond/Desktop/Github/Medeniyetin-Burclari-IHA/ESP/ESPNOW/Reciever/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/diamond/Desktop/Github/Medeniyetin-Burclari-IHA/ESP/ESPNOW/Reciever/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
