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
        'modules/foundation/',
        'include/',
      ],

      'sources': [
        'include/abot/foundation.h',
		
        'modules/foundation/FoundationCommon.h',

        'modules/foundation/Component.h',
        'modules/foundation/Container.h',

        'modules/foundation/Group.h',
        'modules/foundation/Group.cpp',
        'modules/foundation/Node.h',
        'modules/foundation/Node.cpp',
        'modules/foundation/SignalSlot.h',
        'modules/foundation/Foundation.cpp',
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