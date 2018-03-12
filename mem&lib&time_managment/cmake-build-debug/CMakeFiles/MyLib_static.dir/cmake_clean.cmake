file(REMOVE_RECURSE
  "libMyLib_static.pdb"
  "libMyLib_static.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/MyLib_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
