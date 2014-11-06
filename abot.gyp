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
  'target_defaults': {
    'defines': [
    ],
    'variables': {
    },
    'conditions': [
      ['OS=="win"', {
        'configurations': {
          'Debug': {
            'msvs_settings': {
              'VCCLCompilerTool': {
                'RuntimeLibrary': '1',
                'Optimization': '0',
                'DebugInformationFormat': '4',
              },
              'VCLinkerTool': {
                'GenerateDebugInformation': 'true',
                'GenerateMapFile': 'false',
                'SubSystem': '1',
              },
            }, # msvs_settings
          }, # Debug
          'Release': {
            'msvs_settings': {
              'VCCLCompilerTool': {
                'RuntimeLibrary': '0',
                'Optimization': '2',
                'EnableIntrinsicFunctions': 'true',
                'DebugInformationFormat': '3',
              },
              'VCLinkerTool': {
                'GenerateDebugInformation': 'true',
                'GenerateMapFile': 'false',
              },
            }, # msvs_settings
          }, # Release
        }, # configurations
      }], # Windows
      ['OS=="mac"', {
        'make_global_settings': [
          ['CC', '/usr/bin/clang'],
          ['CXX', '/usr/bin/clang++'],
         ],
        
        'defines': [
          'OS_POSIX',
          'OS_MACOSX',
        ],
        'xcode_settings': {
          'ALWAYS_SEARCH_USER_PATHS': 'NO',
          #'i386', 'x86_64'
          'ARCHS': [ 'x86_64' ],
          'MACOSX_DEPLOYMENT_TARGET': '10.6',
          'CC': 'clang',
          'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
          'CLANG_CXX_LANGUAGE_STANDARD': 'c++0x',
          # libstdc++, c++11, libc++
          'CLANG_CXX_LIBRARY': 'libstdc++',
          'GCC_ENABLE_OBJC_GC': 'unsupported',
          #'LIBRARY_SEARCH_PATHS': [],
          'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
          'GCC_SYMBOLS_PRIVATE_EXTERN': 'NO',
          'DEBUG_INFORMATION_FORMAT': 'dwarf-with-dsym',
          #'DEPLOYMENT_POSTPROCESSING': 'YES',
          'OTHER_CFLAGS': [
            '-fno-eliminate-unused-debug-symbols',
            '-mmacosx-version-min=10.6',
            # compile use oc++
            '-x objective-c++',
          ],
          'WARNING_CFLAGS': ['-Wno-deprecated-declarations'],
          'WARNING_CFLAGS!': ['-Wall', '-Wextra',],
          'WARNING_CXXFLAGS': ['-Wstrict-aliasing', '-Wno-deprecated',],
        }, # xcode_settings
        'link_settings': {
          'libraries': [
            '$(SDKROOT)/System/Library/Frameworks/Foundation.framework',
          ],
        },
        'libraries': [],
        'mac_framework_dirs': [],
        'configurations': {
          'Debug': {
            'xcode_settings': {
              'GCC_DEBUGGING_SYMBOLS': 'full',
              'STRIP_INSTALLED_PRODUCT': 'YES',
              'GCC_OPTIMIZATION_LEVEL': '0',
              'OTHER_CFLAGS': ['-g',],
              'OTHER_CXXFLAGS': ['-g',],
            }, # xcode_settings
          }, # Debug
          'Release': {
            'xcode_settings': {
              'GCC_OPTIMIZATION_LEVEL': 's',
            }, # xcode_settings
          }, # Release
        }, # configurations
      }], # Mac
      ['OS=="linux"', {
        'defines': [
          'OS_POSIX',
          'OS_LINUX',
        ],
        'cflags': [
          # Support 64-bit shared libs (also works fine for 32-bit).
          '-fPIC',
          '-std=c++11',
          '-fstrict-aliasing',
          '-Wall',
          '-Wextra',
          '-Wshadow',
          '-Wconversion',
          #'-Wpadded',
          '-Wstrict-aliasing=2',
          '-Wstrict-overflow=4',
        ],
        'ldflags': [],
        'configurations': {
          'Debug': {
            'cflags': [
              '-g',
              '-C',
            ],
          },
          'Release': {
            'cflags': [
              '-O2',
            ],
          },
        }, # configurations
      }],
    ],
  },
  'targets': [
    {
      'target_name': 'foundation',
      'type': 'executable',

      'variables': {
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
        #'target_arch="x86, x86_64"',
      ],

      'conditions': [
        ['OS=="win"', {
          'defines': [
            'WIN32',
            'UNICODE',
            '_UNICODE',
            'OS_WIN',
          ],
          'msbuild_configuration_attributes': {
            #'IntermediateDirectory': '$(OutDir)__BuildTemp\\$(ProjectName)\\',
          },
          'msbuild_toolset': {
            #'PlatformToolset': 'v100'
          }, # msbuild_toolset
          'msvs_settings': {
            'VCCLCompilerTool': {
              'WarningLevel': '3',
              'DisableSpecificWarnings': ['4251','4996'],
              'WarnAsError': 'true',
            },
            'VCLinkerTool': {
              'AdditionalDependencies': [
                'kernel32.lib',
                'user32.lib',
              ],
              'AdditionalLibraryDirectories': [],
            },
          }, # msvs_settings
        }], # Linux
      ], # conditions
    },
  ], # end targets
}