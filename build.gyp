{
  'includes': [ 'common.gypi' ],
  'targets': [
    {
      'target_name': 'libhh',
      'type': 'executable',
      'sources': [
        'src/libhh.c',
      ],
      'dependencies': [
        './deps/libuv/uv.gyp:libuv',
      ],
    }
  ]
}
