import os
env = Environment(ENV = os.environ)

# enable choosing other compilers
env["CC"] = os.getenv("CC") or env["CC"]
env["CXX"] = os.getenv("CXX") or env["CXX"]
env["ENV"].update(x for x in os.environ.items() if x[0].startswith("CCC_"))

def CheckPKGConfig(context, version):
	context.Message( 'Checking for pkg-config... ' )
	ret = context.TryAction('pkg-config --atleast-pkgconfig-version=%s' % version)[0]
	context.Result( ret )
	return ret
def CheckPKG(context, name):
	context.Message( 'Checking for %s... ' % name )
	ret = context.TryAction('pkg-config --exists \'%s\'' % name)[0]
	context.Result( ret )
	return ret

conf = Configure(env, custom_tests = { 'CheckPKGConfig' : CheckPKGConfig,
	'CheckPKG' : CheckPKG })

if not conf.CheckPKGConfig('0.15.0'):
	print 'pkg-config >= 0.15.0 not found.'
	Exit(1)
if not conf.CheckPKG('sdl2'):
	print 'sdl 2.x not found.'
	Exit(1)

env = conf.Finish()

env.Append(CPPPATH = ['#include/'])
env.Append(LIBPATH = ['#src/'])
env.Append(LIBS = ['-lSDL2_ttf', '-lSDL2_image'])
env.Append(CFLAGS = ['-g'])
env.Append(CPPFLAGS = ['-g'])

Export("env")

# Main static library
SConscript('src/SConscript')

# Example code
SConscript('examples/SConscript')
