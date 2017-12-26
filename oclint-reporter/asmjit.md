xlearn统计信息
=======================
### k405(InvalidPointToLocalVariable)
1.1 [codebuilder.cpp 91](asmjit/src/asmjit/base/codebuilder.cpp)<br>
错误信息: Pointer to local variable 'node' is stored outside the scope of this variable. Such a pointer will become invalid.<br>
代码:
```
Error CodeBuilder::getCBLabel(CBLabel** pOut, uint32_t id) noexcept {
   ...
   CBLabel* node = _cbLabels[index];
   if (!node) {
     node = newNodeT<CBLabel>(id);
     if (ASMJIT_UNLIKELY(!node))
       return DebugUtils::errored(kErrorNoHeapMemory);
     _cbLabels[index] = node;
   }

   *pOut = node;
   return kErrorOk;
 }
```
1.2 [codeholder.cpp 282:3](asmjit/src/asmjit/base/codeholder.cpp)<br>
错误信息: Pointer to local variable 'node' is stored ...<br>
代码:
```
 static Error CodeHolder_reserveInternal(CodeHolder* self, CodeBuffer* cb, size_t n) noexcept {
   uint8_t* oldData = cb->_data;
   uint8_t* newData;

   if (oldData && !cb->isExternal())
     newData = static_cast<uint8_t*>(Internal::reallocMemory(oldData, n));
   else
     newData = static_cast<uint8_t*>(Internal::allocMemory(n));

   if (ASMJIT_UNLIKELY(!newData))
     return DebugUtils::errored(kErrorNoHeapMemory);

   cb->_data = newData;
   cb->_capacity = n;
   ...
   return kErrorOk;
 }
```
1.3 [codeholder.cpp 414:3](asmjit/src/asmjit/base/codeholder.cpp)<br>
错误信息: Pointer to local variable 'link' is stored ...<br>
代码:
```
LabelLink* CodeHolder::newLabelLink(LabelEntry* le, uint32_t sectionId, size_t offset, intptr_t rel) noexcept {
   LabelLink* link = _baseHeap.allocT<LabelLink>();
   if (ASMJIT_UNLIKELY(!link)) return nullptr;

   link->prev = le->_links;
   le->_links = link;

   link->sectionId = sectionId;
   link->relocId = RelocEntry::kInvalidId;
   link->offset = offset;
   link->rel = rel;

   _unresolvedLabelsCount++;
   return link;
 }
```
1.4 [codeholder.cpp 556:3](asmjit/src/asmjit/base/codeholder.cpp)<br>
错误信息: Pointer to local variable 're' is stored ...<br>
代码:
```
 Error CodeHolder::newRelocEntry(RelocEntry** dst, uint32_t type, uint32_t size) noexcept {
   ASMJIT_PROPAGATE(_relocations.willGrow(&_baseHeap));

   size_t index = _relocations.getLength();
   if (ASMJIT_UNLIKELY(index > size_t(0xFFFFFFFFU)))
     return DebugUtils::errored(kErrorRelocIndexOverflow);

   RelocEntry* re = _baseHeap.allocZeroedT<RelocEntry>();
   if (ASMJIT_UNLIKELY(!re))
     return DebugUtils::errored(kErrorNoHeapMemory);

   re->_id = static_cast<uint32_t>(index);
   re->_type = static_cast<uint8_t>(type);
   re->_size = static_cast<uint8_t>(size);
   re->_sourceSectionId = SectionEntry::kInvalidId;
   re->_targetSectionId = SectionEntry::kInvalidId;
   _relocations.appendUnsafe(re);

   *dst = re;
   return kErrorOk;
 }

```
1.5 [constpool.cpp 101:5](asmjit/src/asmjit/base/constpool.cpp)<br>
错误信息: Pointer to local variable 'link' is stored ...<br>
代码:
```
 static void ConstPool_addGap(ConstPool* self, size_t offset, size_t length) noexcept {
   ASMJIT_ASSERT(length > 0);

   while (length > 0) {
     size_t gapIndex;
     size_t gapLength;

     gapIndex = ConstPool::kIndex16;
     ...
     ConstPool::Gap* gap = ConstPool_allocGap(self);
     if (!gap) return;

     gap->_next = self->_gaps[gapIndex];
     self->_gaps[gapIndex] = gap;
     ...
   }
```
同样问题发生在[asmjit/src/asmjit/base/constpool.cpp 205:5](asmjit/src/asmjit/base/constpool.cpp)<br>
1.6 [asmjit/src/asmjit/base/regalloc.cpp 201:3](asmjit/src/asmjit/base/regalloc.cpp)<br>
错误信息: Pointer to local variable 'cell' is stored ...<br>
1.7 [string.cpp 70](asmjit/src/asmjit/base/string.cpp)<br>
错误信息: Pointer to local variable 'newData' is stored ...<br>
```
 if (_capacity < len) {
       ...
       char* newData = static_cast<char*>(Internal::allocMemory(to + sizeof(intptr_t)));
       if (!newData) {
         clear();
         return nullptr;
       }

       if (_canFree)
         Internal::releaseMemory(_data);

       _data = newData;
       _capacity = to + sizeof(intptr_t) - 1;
       _canFree = true;
     }

     _data[len] = 0;
     _length = len;

     ASMJIT_ASSERT(_length <= _capacity);
     return _data;
```
同样问题发生在115行，146行
发生在其他文件[asmjit/src/asmjit/base/zone.cpp 154](asmjit/src/asmjit/base/zone.cpp)
493行， 789行， 错误信息: Pointer to local variable 'newData' is stored ...<br>
发生在其他文件[asmjit/src/asmjit/base/zone.cpp 493](asmjit/src/asmjit/base/zone.cpp)
错误信息: Pointer to local variable 'newData' is stored ...<br>
1.8 [vmem.cpp 292](asmjit/src/asmjit/base/vmem.cpp)<br>
错误信息: Pointer to local variable 'vmem' is stored ...<br>
```
static MemNode* vMemMgrCreateNode(VMemMgr* self, size_t size, size_t density) noexcept {
   size_t vSize;
   uint8_t* vmem = vMemMgrAllocVMem(self, size, &vSize);
   if (!vmem) return nullptr;
    ... 
   MemNode* node = static_cast<MemNode*>(Internal::allocMemory(sizeof(MemNode)));
   uint8_t* data = static_cast<uint8_t*>(Internal::allocMemory(bsize * 2));
   ...
   node->mem = vmem;
   node->red = 1;
   ...
   return node;
}
```
1.9 [asmjit/src/asmjit/x86/x86regalloc.cpp 1187](asmjit/src/asmjit/x86/x86regalloc.cpp)
错误信息: Pointer to local variable 'cReg' is stored ...<br>
同样问题发生在1188行，146行
2.0 [asmjit/src/asmjit/base/zone.cpp 662](asmjit/src/asmjit/base/zone.cpp)<br>
错误信息: Pointer to local variable 'block' is stored ...<br>
```
 if (heap) {
     Block* block = static_cast<Block*>(heap->alloc(kBlockSize));
     if (ASMJIT_UNLIKELY(!block))
       return DebugUtils::errored(kErrorNoHeapMemory);

     block->_link[kSideLeft] = nullptr;
     block->_link[kSideRight] = nullptr;
     block->_start = (uint8_t*)block + middleIndex;
     block->_end = (uint8_t*)block + middleIndex;

     _heap = heap;
     _block[kSideLeft] = block;
     _block[kSideRight] = block;
   }
```
同样问题663行，688, 689
2.1 [asmjit/src/asmjit/x86/x86regalloc.cpp 3749](asmjit/src/asmjit/x86/x86regalloc.cpp) <br>
错误信息: Pointer to local variable 'injectLabel' is stored ...<br>
代码:
```
{
    ...
   if (cc->getCursor() != injectRef) {
     // TODO: Can fail.
     CBLabel* injectLabel = cc->newLabelNode();
     ...
     jNode->_target = injectLabel;
     // If we injected any code it may not satisfy short form anymore.
     jNode->delOptions(X86Inst::kOptionShortForm);
   }
 
   cc->_setCursor(prevCursor);
   self->loadState(jNode->getPassData<RAData>()->state);
 }
```

2.2 [asmjit/src/asmjit/x86/x86regalloc.cpp 3986](asmjit/src/asmjit/x86/x86regalloc.cpp)  variable 'savedState' <br>
同样3995行<br>
### k407(OperationLogicNotCorrespondWithItsFormat)
1.1 [asmjit/src/asmjit/base/codeholder.cpp 435](asmjit/src/asmjit/base/codeholder.cpp)<br>
```
   if (ASMJIT_UNLIKELY(!le))
     return DebugUtils::errored(kErrorNoHeapMemory);;
```
同样问题 [asmjit/src/asmjit/base/string.cpp 287](asmjit/src/asmjit/base/string.cpp)<br>
### k409(AssignSameVariableTwiceSuccessively)
1.1 [asmjit/src/asmjit/base/constpool.cpp 116](asmjit/src/asmjit/base/constpool.cpp)<br>
错误: The 'node' object is assigned values twice successively. Perhaps this is a mistake.<br>
代码:
```
     node = ConstPoolTree_skewNode(node);
     node = ConstPoolTree_splitNode(node);
```
### k410(SameReturnValueOfConditionalOperator)
1.1 [asmjit/src/asmjit/x86/x86assembler.cpp 253](asmjit/src/asmjit/x86/x86assembler.cpp)<br>
错误信息:the conditional operation '(LL==1) ? 0 : 0' always returns the same value '0'.<br>
代码:
```
     kValue = (TT == X86Inst::kOpCode_CDTT_None ? ((LL==0) ? 0 : (LL==1) ? 0   : 0  ) :
               TT == X86Inst::kOpCode_CDTT_ByLL ? ((LL==0) ? 0 : (LL==1) ? 1   : 2  ) :
               TT == X86Inst::kOpCode_CDTT_T1W  ? ((LL==0) ? W : (LL==1) ? 1+W : 2+W) :
               TT == X86Inst::kOpCode_CDTT_DUP  ? ((LL==0) ? 0 : (LL==1) ? 2   : 3  ) : 0 ) << X86Inst::kOpCode_CDSHL_Shift
```
### k413(PointerUnaryAndDerefConfuse)
1.1 [asmjit/src/asmjit/base/vmem.cpp 85](asmjit/src/asmjit/base/vmem.cpp)<br>
```
 while (i < blocks) {
       ubits = *up++;
       ...
 }
```
1.2 [asmjit/src/asmjit/x86/x86assembler.cpp 4584](asmjit/src/asmjit/x86/x86assembler.cpp)<br>
```
         do {
             EMIT_BYTE(*src++);
           } while (--n);

```
### 415(ContinueWillTerminateDoWhileFalseLoop)
错误：false condition
```
   do {
      ...
   } while (false);
```
### k416(UnconditionalBreakWithinALoop)
1.1 [asmjit/src/asmjit/x86/x86regalloc.cpp 3265](asmjit/src/asmjit/x86/x86regalloc.cpp)<br>
错误信息: An unconditional 'continue' within a loop.
```
 for (i = 0; i < tiedCount; i++) {
    ...
     continue;
   }

```
