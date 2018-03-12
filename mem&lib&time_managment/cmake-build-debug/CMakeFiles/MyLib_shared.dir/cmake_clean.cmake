file(REMOVE_RECURSE
  "libMyLib_shared.pdb"
  "libMyLib_shared.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/MyLib_shared.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
