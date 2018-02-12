## DCDR Project coding guidelines 

### Common
- Don't repeat yourself

### C++

##### Rules
- Do not use macros in header files
- Use `#include <file.h>` for public includes (e.g other module, library or public includes of current library)
- Use `#include "file.h"` for private includes (e.g placed in `private` folder within corrent module)
- Define virtual destructor for abstract/interface classes. Use `virtual ~Class() = default` syntax
- Use anonymous namespace for function/classes which are private to the current source file. 

##### Recommendations
- Do not use macros at all
- Minimize actual implementation details in header files - use pimpl pattern where applicable
- Minimize usage of dynamic_cast. Use visitor pattern instead if possible.
- Use forward declarations where possible
- Try to keep code coverage at high level

### FlatBuffers

##### Rules
- Place all code inside DcdrFlatBuffers namespace

##### Recomendations
- Do not make huge unreadable few-hundred-lined schema files. Separate these huge files on few shorter files. 