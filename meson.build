project('DidDo', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

include_dir = include_directories('./include')

DidDo = executable('DidDo', 'src/main.cpp', include_directories : include_dir, install : true)

#test('test', DidDo)