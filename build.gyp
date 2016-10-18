{
  'includes': [ 'common.gypi' ],
  'targets': [
    {
      'target_name': 'libhh',
      'type': 'executable',
      'sources': [
        'src/libhh.c',
        'src/net/server.h',
        'src/net/server.c',
        'src/net/message_handler.h',
        'src/net/message_handler.c',
        'src/net/handlers/handshake_handler.h',
        'src/net/buffer/buffer.h',
        'src/net/buffer/buffer.c',
      ],
      'dependencies': [
        './deps/libuv/uv.gyp:libuv',
      ],
    }
  ]
}
