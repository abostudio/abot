{
  #
  'variables': {

    'library_files': [
    ],
  },
  'defines': [
  ],
  'includes': [
  ],
  'targets': [
    {
      'target_name': 'foundation',
      'type': 'executable',

      'variables': {
        #'optimize': 'max',
      },

      'dependencies': [
        #'js2c',
        'third_party/v8/tools/gyp/v8.gyp:v8',
        'third_party/v8/tools/gyp/v8.gyp:v8_libplatform'
      ],

      'include_dirs': [
        'third_party/v8/',
        'modules/foundation',
      ],

      'sources': [
        'third_party/v8/include/v8.h',
        'third_party/v8/include/v8-debug.h',
        'modules/foundation/foundation.cpp',
      ],

      'defines': [
        'target_arch="x86"',
      ],

      'conditions': [
      ],
      'msvs_settings': {
        'VCLinkerTool': {
          'SubSystem': 1, # /subsystem:console
        },
		'VCCLCompilerTool': {
          'Optimization': '0',
          'RuntimeLibrary': 1, # multi threaded static
        },
      },
    },
  ], # end targets
  'conditions': [
    #['OS=="linux"', {
	#  
    #}],
    #['OS=="win"', {
    #  '_UNICODE=1',
    #  'PLATFORM="win32"',
    #}, { #'OS != "win"'
    #}],
   ],
  
}