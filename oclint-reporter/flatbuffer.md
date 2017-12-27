flatbuffer统计信息
=======================
### k405(InvalidPointToLocalVariable)
1.1 [flatbuffers/src/idl_parser.cpp 563:3 ](flatbuffers/src/idl_parser.cpp#L563)<br>
错误信息: Pointer to local variable 'field' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
代码:
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
错误信息: Pointer to local variable 'struct_def' is stored outside ...<br>
1.3 [flatbuffers/src/idl_parser.cpp 2203:3 ](flatbuffers/src/idl_parser.cpp#L2203)<br>
错误信息: Pointer to local variable 'current_directory' is stored ...<br>
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
1.4 [flatbuffers/src/flatc_main.cpp 107:3](flatbuffers/src/flatc_main.cpp#L107)<br>
错误信息: Pointer to local variable 'generators' is stored outside the scope...<br>
```
int main(int argc, const char *argv[]) {
   g_program_name = argv[0];

   const flatbuffers::FlatCompiler::Generator generators[] = {
     { flatbuffers::GenerateBinary,   "-b", "--binary", "binary", false,
       nullptr,
       flatbuffers::IDLOptions::kBinary,
       "Generate wire format binaries for any data definitions",
       flatbuffers::BinaryMakeRule },
       ...
       };

   flatbuffers::FlatCompiler::InitParams params;
   params.generators = generators;
   params.num_generators = sizeof(generators) / sizeof(generators[0]);
   params.warn_fn = Warn;
   params.error_fn = Error;

   flatbuffers::FlatCompiler flatc(params);
   return flatc.Compile(argc - 1, argv + 1);
 }
```
### k413(PointerUnaryAndDerefConfuse)
1.1 [flatbuffers/src/idl_parser.cpp 247](flatbuffers/src/idl_parser.cpp#L247) <br>
错误信息: Consider inspecting the statement of '*pointer++' pattern. Probably meant: '(*pointer)++'.<br>
代码:
```
char c = *cursor_++;
```
1.2 [flatbuffers/src/idl_parser.cpp 327](flatbuffers/src/idl_parser.cpp#L327) <br>
### k417(RecuringCheck)
1.1 [flatbuffers/src/idl_gen_general.cpp 810](flatbuffers/src/idl_gen_general.cpp#L810)<br>
信息: Recurring check. The IF Condition 'lang\_.language == IDLOptions::kCSharp' check twice.<br>
代码:
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
