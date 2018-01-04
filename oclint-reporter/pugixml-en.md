pugixml defect information
=======================
### k404(TwoFunctionBodyEquivalenit)
**Explanation of k404:** the body of two function equals, Perhaps write just one.<br>
1.1 [pugixml/src/pugixml.cpp 12706](pugixml/src/pugixml.cpp#L12706-#L12709) <br>
**error message:** It is odd that the body of 'select_node(line:12685-12687)' function is fully equivalent to the body of 'select_single_node(line:12707-12709)' function.<br>
**code sample:**
```
    PUGI__FN xpath_node xml_node::select_node(const xpath_query& query) const
     {
         return query.evaluate_node(*this);
     }
     ...
     PUGI__FN xpath_node_set xml_node::select_nodes(const xpath_query& query) const
     {
         return query.evaluate_node_set(*this);
     }
```
### k405(InvalidPointToLocalVariable)
**Explanation of k405:** a Pointer variable pointing to a local variable, when using the pointer out of the scope of local variable, The pointer will become Invalid.<br>
1.1 [pugixml/src/pugixml.cpp 6083](pugixml/src/pugixml.cpp#L6083)<br>
**error message:** Pointer to local variable 'extra' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
**code sample：**
```
PUGI__FN xml_parse_result xml_node::append_buffer(const void* contents, size_t size, unsigned int options, xml_encoding encoding)
     {
         ...
         // get document node
         impl::xml_document_struct* doc = &impl::get_document(_root);
         ...
         impl::xml_extra_buffer* extra = static_cast<impl::xml_extra_buffer*>(doc->allocate_memory(sizeof(impl::xml_extra_buffer), page));
         ...
         doc->extra_buffers = extra;
         ...
     }
```
1.2 [pugixml/src/pugixml.cpp 12036](pugixml/src/pugixml.cpp#L12036)<br>
**error message:** Pointer to local variable 'storage' is stored outside ...<br>
**code sample:**
```
            xpath_node* storage = static_cast<xpath_node*>(impl::xml_memory::allocate(size_ * sizeof(xpath_node)));
            ...
             _begin = storage;
             ...
```
same error in [12243](pugixml/src/pugixml.cpp#L12243)line error message: Pointer to local variable 'copy' is stored outside the scope...<br>
