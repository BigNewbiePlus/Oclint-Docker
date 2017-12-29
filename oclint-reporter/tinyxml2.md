tinyxml2统计信息
=======================
### k405(InvalidPointToLocalVariable)
1.1 [tinyxml2/tinyxml2.cpp 721:5 ](tinyxml2/tinyxml2.cpp#L721)<br>
错误信息: Pointer to local variable 'returnNode' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
代码:
```
 char* XMLDocument::Identify( char* p, XMLNode** node )
 {
     ...
    XMLNode* returnNode = 0;
     if ( XMLUtil::StringEqual( p, xmlHeader, xmlHeaderLen ) ) {
         returnNode = CreateUnlinkedNode<XMLDeclaration>( _commentPool );
         returnNode->_parseLineNum = _parseCurLineNum;
         p += xmlHeaderLen;
     }
     *node = returnNode;
     ...
 }
```
### k424(CmpFuncUseInCondition)
1.1 [tinyxml2/xmltest.cpp 700](tinyxml2/xmltest.cpp#L397) <br>
错误信息: The 'strcmp' function returns 0 if corresponding strings are equal. Consider examining the condition for mistakes.<br>
代码:
```
                if ( strcmp( verifyBuf, savedBuf ) )
                {
                     printf( "verify:%s<\n", verifyBuf );
                     printf( "saved :%s<\n", savedBuf );
                     roundTripOkay = false;
                     break;
                 }

```
