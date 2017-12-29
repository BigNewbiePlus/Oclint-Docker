tinyxml2 defact information
=======================
### k405(InvalidPointToLocalVariable)
Explanation of k405 : **a Pointer variable pointing to a local variable, when using the pointer out of the scope of local variable, The pointer will become Invalid.**<br>
1.1 [tinyxml2/tinyxml2.cpp 721:5 ](tinyxml2/tinyxml2.cpp#L721)<br>
error message: Pointer to local variable 'returnNode' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
sample code:
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
Explanation of k424: **strcmp function return 0 when two strings equal, check when using in condition.**
1.1 [tinyxml2/xmltest.cpp 397](tinyxml2/xmltest.cpp#L397) <br>
error message: The 'strcmp' function returns 0 if corresponding strings are equal. Consider examining the condition for mistakes.<br>
code sample:
```
                if ( strcmp( verifyBuf, savedBuf ) )
                {
                     printf( "verify:%s<\n", verifyBuf );
                     printf( "saved :%s<\n", savedBuf );
                     roundTripOkay = false;
                     break;
                 }

```
