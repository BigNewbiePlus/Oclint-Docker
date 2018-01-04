flatbuffer defact information
=======================
### k405(InvalidPointToLocalVariable)
**Explanation of k405：** a Pointer variable pointing to a local variable, when using the pointer out of the scope of local variable, The pointer will become Invalid.<br>
1.1 [flatbuffers/src/idl_parser.cpp 563:3 ](flatbuffers/src/idl_parser.cpp#L563)<br>
**error message:** Pointer to local variable 'field' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
**code sample:**
```
CheckedError Parser::AddField(StructDef &struct_def, const std::string &name,
                               const Type &type, FieldDef **dest) {
   auto &field = *new FieldDef();
   ...
   *dest = &field;
   return NoError();
 }
```
1.2 [flatbuffers/src/idl_parser.cpp 1517:3 ](flatbuffers/src/idl_parser.cpp#L1517) <br>
**error message:** Pointer to local variable 'struct_def' is stored outside ...<br>
1.3 [flatbuffers/src/idl_parser.cpp 2203:3 ](flatbuffers/src/idl_parser.cpp#L2203)<br>
**error message:** Pointer to local variable 'current_directory' is stored ...<br>
```
 CheckedError Parser::DoParse(const char *source,
                                     const char **include_paths,
                                     const char *source_filename,
                                     const char *include_filename) {
   ...
   if (!include_paths) {
     static const char *current_directory[] = { "", nullptr };
     include_paths = current_directory;
   }
   ...
 }
 ```
### k413(PointerUnaryAndDerefConfuse)
**Explanation of k413:** unary operator(++,--) and dereference of a pointer occur at the same time.The priority is unclear.<br>
1.1 [flatbuffers/src/idl_parser.cpp 247](flatbuffers/src/idl_parser.cpp#L247) <br>
**error message:** Consider inspecting the statement of '\*pointer++' pattern. Probably meant: '(\*pointer)++'.<br>
**code sample:**
```
char c = *cursor_++;
```
1.2 [flatbuffers/src/idl_parser.cpp 327](flatbuffers/src/idl_parser.cpp#L327) <br>
### k417(RecuringCheck)
**Explanation of k417:** Recurring check of condtion.<br>
1.1 [flatbuffers/src/idl_gen_general.cpp 810](flatbuffers/src/idl_gen_general.cpp#L810)<br>
**error message:** Recurring check. The IF Condition 'lang\_.language == IDLOptions::kCSharp' check twice.<br>
**code sample:**
```
if (lang_.language == IDLOptions::kCSharp) {
     code += " : IFlatbufferObject";
     code += lang_.open_curly;
     code += "  private ";
     code += struct_def.fixed ? "Struct" : "Table";
     code += " __p;\n";

     if (lang_.language == IDLOptions::kCSharp) {
         code += "  public ByteBuffer ByteBuffer { get { return __p.bb; } }\n";
     }

   }
```
