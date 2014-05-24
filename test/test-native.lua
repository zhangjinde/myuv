local uv = require('native')

local r = uv.run('nowait')
print('nowait', r)

r = uv.run('once')
print('once', r)

local now = uv.now()
print('now', now)