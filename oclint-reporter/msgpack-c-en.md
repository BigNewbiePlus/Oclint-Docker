msgpack-c defect info
=======================
### k401(NonVoidFunctionShouldReturnAValue)
**Explanation of k401:** The function should return a value according to the definition, however, it not.<br>
1.1 [msgpack-c/example/cpp03/custom.cpp 34](msgpack-c/example/cpp03/custom.cpp#L34)<br>
**error message:** non-void function 'main' should return a value<br>
**code sample:**
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
same error in [msgpack-c/example/cpp03/class_intrusive_map.cpp 54:1](msgpack-c/example/cpp03/class_intrusive_map.cpp#L54)
### k405(InvalidPointToLocalVariable)
**Explanation of k405:** a Pointer variable pointing to a local variable, when using the pointer out of the scope of local variable, The pointer will become Invalid.<br>
1.1 [msgpack-c/src/unpack.c 496](msgpack-c/src/unpack.c#L496)<br>
**error message:** Pointer to local variable 'r' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
**code sample：**
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
same error in [msgpack-c/src/vrefbuffer.c 113](msgpack-c/src/vrefbuffer.c#L113) error info: Pointer to local variable 'nvec' is stored outside ...<br>
same error in [msgpack-c/src/vrefbuffer.c 145](msgpack-c/src/vrefbuffer.c#L145) error info: Pointer to local variable 'chunk' is stored outside ...<br>
same error in [msgpack-c/src/vrefbuffer.c 199](msgpack-c/src/vrefbuffer.c#L199) error info: Pointer to local variable 'nvec' is stored outside ...<br>
1.2 [msgpack-c/src/zone.c 27](msgpack-c/src/zone.c#L27)<br>
**error message** Pointer to local variable 'chunk' is stored outside ...<br>
**code sample:**
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
