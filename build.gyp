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
        'src/net/handlers/catalog/catalog_handler.h',
        'src/net/handlers/catalog/catalog_handler.c',
        'src/net/handlers/messenger/messenger_handler.h',
        'src/net/handlers/messenger/messenger_handler.c',
        'src/net/composers/handshake_composers.h',
        'src/net/composers/handshake_composers.c',
        'src/net/composers/player_composers.h',
        'src/net/composers/player_composers.c',
        'src/net/composers/catalog_composers.h',
        'src/net/composers/catalog_composers.c',
        'src/net/composers/messenger_composers.h',
        'src/net/composers/messenger_composers.c',
        'src/net/composers/composers.h',
        'src/net/sessions/session.h',
        'src/net/sessions/session.c',
        'src/net/events/events.h',
        'src/players/player.h',
        'src/players/player.c',
        'src/players/auth.h',
        'src/players/auth.c',
        'src/catalog/catalog.h',
        'src/catalog/catalog.c',
        'src/util/hashmap.h',
        'src/util/hashmap.c',
        'src/storage/storage.h',
        'src/storage/storage.c',
        'src/storage/sqlite/player_dao.h',
        'src/storage/sqlite/database.h',
        'src/storage/sqlite/database.c',
        'src/storage/'
        'src/util/pool.h',
        'src/util/pool.c'
      ],
      'dependencies': [
        './deps/libuv/uv.gyp:libuv'
      ],
      'link_settings': {
        'libraries': ['-lsqlite3'],
      },
    }
  ]
}
