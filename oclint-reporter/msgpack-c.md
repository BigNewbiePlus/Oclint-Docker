msgpack-c统计信息
=======================
### k404(TwoFunctionBodyEquivalenit)
错误信息: non-void function 'main' 函数没有返回值<br>
代码:
```
 int main(void)
 {
     {
         old_class oc;
         new_class nc;

         std::stringstream sbuf;
         msgpack::pack(sbuf, oc);

         msgpack::object_handle oh =
             msgpack::unpack(sbuf.str().data(), sbuf.str().size());
         msgpack::object obj = oh.get();

         obj.convert(nc);

         std::cout << obj << " value=" << nc.value << " flag=" << nc.flag << std::endl;
     }

     {
         new_class nc;
         old_class oc;

         std::stringstream sbuf;
         msgpack::pack(sbuf, nc);

         msgpack::object_handle oh =
             msgpack::unpack(sbuf.str().data(), sbuf.str().size());
         msgpack::object obj = oh.get();

         obj.convert(oc);

         std::cout << obj << " value=" << oc.value << std::endl;
     }
 }
```
另外还有10处同样情况
### k405(InvalidPointToLocalVariable)
1.1 [msgpack-c/src/unpack.c 496](msgpack-c/src/unpack.c#L496)<br>
错误信息: Pointer to local variable 'r' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
代码：
```
 msgpack_zone* msgpack_unpacker_release_zone(msgpack_unpacker* mpac)
 {
     msgpack_zone* r;
     ...
     r = msgpack_zone_new(MSGPACK_ZONE_CHUNK_SIZE);
     if(r == NULL) {
         return NULL;
     }

     ...
     mpac->z = r;
     CTX_CAST(mpac->ctx)->user.z = mpac->z;

     return old;
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
