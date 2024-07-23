## windows-process-info
Easily check if a process with a given name is running on Windows. Should take <10ms to execute for both existing and non-existing processes, which makes it much faster than any `execSync()` hacks.

```
npm install windows-process-info
```

```js
const { isProcessRunning } = require('windows-process-info`)
const isVisualStudioCodeRunning = isProcessRunning('Code.exe')
```

Please note that process names are case-sensitive.

#### License
MIT, please see LICENSE for details. Copyright (c) 2024 Felix Rieseberg.
