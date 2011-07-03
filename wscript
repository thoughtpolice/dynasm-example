# -*- Python -*-
APPNAME = 'nikto'
VERSION = '0.0.1'
top     = '.'
out     = '.wafbuild'

def options(opt):
	opt.load('compiler_c')

def configure(ctx):
    ctx.load('compiler_c')
    ctx.recurse('src')

def build(ctx):
	ctx.recurse('src')

