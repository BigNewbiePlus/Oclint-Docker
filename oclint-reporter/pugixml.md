pugixml统计信息
=======================
### k404(TwoFunctionBodyEquivalenit)
1.1 [pugixml/src/pugixml.cpp 12706](pugixml/src/pugixml.cpp) <br>
错误信息: It is odd that the body of 'select_node(line:12685-12687)' function is fully equivalent to the body of 'select_single_node(line:12707-12709)' function.<br>
代码:
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
1.1 [pugixml/src/pugixml.cpp 6083](pugixml/src/pugixml.cpp)<br>
错误信息: Pointer to local variable 'extra' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
代码：
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
1.2 [pugixml/src/pugixml.cpp 12306](pugixml/src/pugixml.cpp)]
信息: Pointer to local variable 'storage' is stored outside ...<br>
```
            xpath_node* storage = static_cast<xpath_node*>(impl::xml_memory::allocate(size_ * sizeof(xpath_node)));
            ...
             _begin = storage;
             ...
```
错误信息: '1' repeated in expression '1==1' !<br>
代码:
```
RAW_CHECK(1 == 1, "should be ok");
```
同样出现在行12243: ointer to local variable 'copy' is stored outside the scope...<br>
