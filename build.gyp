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
        'src/net/handlers/handshake_handler.c',
        'src/net/buffer/buffer.h',
        'src/net/buffer/buffer.c',
        'src/net/handlers/handshake_handler.h',
        'src/net/handlers/handshake_handler.c',
        'src/net/composers/handshake_composers.h',
        'src/net/composers/handshake_composers.c',
        'src/net/composers/composers.h'
      ],
      'dependencies': [
        './deps/libuv/uv.gyp:libuv'
      ]
    }
  ]
}
