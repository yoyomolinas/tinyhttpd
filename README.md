# A Tiny HTTP Server

### Compile
```bash
# server
gcc queue.c tiny.c -o tiny

# client
gcc client.c -o client

```

### Run
```bash
./tiny

# on a separate console run client for testing - alternatvely visit 127.0.0.1:8080
./client
```

By default the server runs on a single thread. Mark the `MULTITHREADED` flag in `tiny.c` for support concurrent requests.

