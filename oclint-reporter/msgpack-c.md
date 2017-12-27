msgpack-c统计信息
=======================
### k404(TwoFunctionBodyEquivalenit)
main函数没有返回值<br>
### k405(InvalidPointToLocalVariable)
1.1 [msgpack-c/src/unpack.c 496](msgpack-c/src/unpack.c#L496)<br>
错误信息: Pointer to local variable 'nvec' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
代码：
```
 int msgpack_vrefbuffer_append_ref(msgpack_vrefbuffer* vbuf,
         const char* buf, size_t len)
 {
     if(vbuf->tail == vbuf->end) {
         ...
         struct iovec* nvec = (struct iovec*)realloc(
                 vbuf->array, sizeof(struct iovec)*nnext);
         ...
         vbuf->array = nvec;
        ...
     }
     ...
 }
```
同样出现在[msgpack-c/src/vrefbuffer.c 113](msgpack-c/src/vrefbuffer.c#L113) 信息: Pointer to local variable 'nvec' is stored outside ...<br>
同样出现在[msgpack-c/src/vrefbuffer.c 145](msgpack-c/src/vrefbuffer.c#L145) 信息: Pointer to local variable 'chunk' is stored outside ...<br>
同样出现在[msgpack-c/src/vrefbuffer.c 199](msgpack-c/src/vrefbuffer.c#L199) 信息: Pointer to local variable 'nvec' is stored outside ...<br>
1.2[msgpack-c/src/zone.c 27](msgpack-c/src/zone.c#L27)<br>
信息: Pointer to local variable 'chunk' is stored outside ...
```
static inline bool init_chunk_list(msgpack_zone_chunk_list* cl, size_t chunk_size)
 {
     msgpack_zone_chunk* chunk = (msgpack_zone_chunk*)malloc(
             sizeof(msgpack_zone_chunk) + chunk_size);
     if(chunk == NULL) {
         return false;
     }

     cl->head = chunk;
     cl->free = chunk_size;
     cl->ptr  = ((char*)chunk) + sizeof(msgpack_zone_chunk);
     chunk->next = NULL;

     return true;
 }
```
