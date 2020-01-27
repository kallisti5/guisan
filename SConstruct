import os
env = Environment(ENV = os.environ)

# enable choosing other compilers
env["CC"] = os.getenv("CC") or env["CC"]
env["CXX"] = os.getenv("CXX") or env["CXX"]
env["ENV"].update(x for x in os.environ.items() if x[0].startswith("CCC_"))

env["LIBVER"] = "0.9.0"

env["PREFIX_PATH"] = ARGUMENTS.get('prefix', "/usr/local")
env["INCLUDE_PATH"] = ARGUMENTS.get('include', env['PREFIX_PATH'] + "/include")
env["LIB_PATH"] = ARGUMENTS.get('lib', env['PREFIX_PATH'] + "/lib")

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
	print('pkg-config >= 0.15.0 not found.')
	Exit(1)

env['HAVE_OPENGL'] = conf.CheckPKG('gl')
env['HAVE_SDL2'] = conf.CheckPKG('sdl2')

if env['HAVE_SDL2']:
	if not conf.CheckPKG('SDL2_image'):
		print('SDL2_image not found. Disabling SDL2 support.')
		env['HAVE_SDL2'] = 0
	if not conf.CheckPKG('SDL2_ttf'):
		print('SDL2_ttf not found. Disabling SDL2 support.')
		env['HAVE_SDL2'] = 0

env = conf.Finish()

env.Append(CPPPATH = ['#include/'])
env.Append(LIBPATH = ['#src/'])
env.Append(CFLAGS = ['-g'])
env.Append(CPPFLAGS = ['-g'])

Export("env")

# Main static library
SConscript('src/SConscript')

# Example code
SConscript('examples/SConscript')

# TODO: install
common_headers = [
    'include/guisan/actionevent.hpp',
    'include/guisan/actionlistener.hpp',
    'include/guisan/basiccontainer.hpp',
    'include/guisan/cliprectangle.hpp',
    'include/guisan/color.hpp',
    'include/guisan/deathlistener.hpp',
    'include/guisan/defaultfont.hpp',
    'include/guisan/event.hpp',
    'include/guisan/exception.hpp',
    'include/guisan/focushandler.hpp',
    'include/guisan/focuslistener.hpp',
    'include/guisan/font.hpp',
    'include/guisan/genericinput.hpp',
    'include/guisan/glut.hpp',
    'include/guisan/graphics.hpp',
    'include/guisan/gui.hpp',
    'include/guisan/imagefont.hpp',
    'include/guisan/image.hpp',
    'include/guisan/imageloader.hpp',
    'include/guisan/inputevent.hpp',
    'include/guisan/input.hpp',
    'include/guisan/keyevent.hpp',
    'include/guisan/key.hpp',
    'include/guisan/keyinput.hpp',
    'include/guisan/keylistener.hpp',
    'include/guisan/listmodel.hpp',
    'include/guisan/mouseevent.hpp',
    'include/guisan/mouseinput.hpp',
    'include/guisan/mouselistener.hpp',
    'include/guisan/opengl.hpp',
    'include/guisan/platform.hpp',
    'include/guisan/rectangle.hpp',
    'include/guisan/sdl.hpp',
    'include/guisan/selectionevent.hpp',
    'include/guisan/selectionlistener.hpp',
    'include/guisan/widget.hpp',
    'include/guisan/widgetlistener.hpp',
    'include/guisan/x.hpp'
]
widget_headers = [
    'include/guisan/widgets/button.hpp',
    'include/guisan/widgets/checkbox.hpp',
    'include/guisan/widgets/container.hpp',
    'include/guisan/widgets/dropdown.hpp',
    'include/guisan/widgets/icon.hpp',
    'include/guisan/widgets/imagebutton.hpp',
    'include/guisan/widgets/imagetextbutton.hpp',
    'include/guisan/widgets/inputbox.hpp',
    'include/guisan/widgets/label.hpp',
    'include/guisan/widgets/listbox.hpp',
    'include/guisan/widgets/messagebox.hpp',
    'include/guisan/widgets/progressbar.hpp',
    'include/guisan/widgets/radiobutton.hpp',
    'include/guisan/widgets/scrollarea.hpp',
    'include/guisan/widgets/slider.hpp',
    'include/guisan/widgets/tabbedarea.hpp',
    'include/guisan/widgets/tab.hpp',
    'include/guisan/widgets/textbox.hpp',
    'include/guisan/widgets/textfield.hpp',
    'include/guisan/widgets/togglebutton.hpp',
    'include/guisan/widgets/window.hpp'
]
sdl2_headers = [
    'include/guisan/sdl/sdlgraphics.hpp',
    'include/guisan/sdl/sdl2graphics.hpp',
    'include/guisan/sdl/sdlimage.hpp',
    'include/guisan/sdl/sdlimageloader.hpp',
    'include/guisan/sdl/sdlinput.hpp',
    'include/guisan/sdl/sdlpixel.hpp',
    'include/guisan/sdl/sdltruetypefont.hpp'
]
opengl_headers = [
    'include/guisan/opengl/openglgraphics.hpp',
    'include/guisan/opengl/openglimage.hpp',
    'include/guisan/opengl/openglsdlimageloader.hpp'
]

env.Install(env["LIB_PATH"], 'src/libguisan.a')
env.Install(env["LIB_PATH"] + "/pkgconfig", 'src/guisan.pc')
env.Install(env["INCLUDE_PATH"], 'include/guisan.hpp')
# install common headers + widgets
env.Install(env["INCLUDE_PATH"] + '/guisan', common_headers)
env.Install(env["INCLUDE_PATH"] + '/guisan/widgets', widget_headers)
if env['HAVE_SDL2']:
	env.Install(env["INCLUDE_PATH"] + '/guisan/sdl', sdl2_headers)
if env['HAVE_OPENGL']:
	env.Install(env["INCLUDE_PATH"] + '/guisan/opengl', opengl_headers)
env.Alias('install', env["PREFIX_PATH"])
