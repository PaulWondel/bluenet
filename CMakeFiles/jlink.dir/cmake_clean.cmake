file(REMOVE_RECURSE
  "tmp/default"
  "CMakeFiles/jlink"
  "CMakeFiles/jlink-complete"
  "jlink-prefix/src/jlink-stamp/jlink-install"
  "jlink-prefix/src/jlink-stamp/jlink-mkdir"
  "jlink-prefix/src/jlink-stamp/jlink-download"
  "jlink-prefix/src/jlink-stamp/jlink-update"
  "jlink-prefix/src/jlink-stamp/jlink-patch"
  "jlink-prefix/src/jlink-stamp/jlink-configure"
  "jlink-prefix/src/jlink-stamp/jlink-build"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/jlink.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
