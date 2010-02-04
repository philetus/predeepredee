<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='en' lang='en'>
<head>
<title>~joonas/cairosdl - Unnamed repository; edit this file to name it for gitweb.</title>
<meta name='generator' content='cgit v0.8.3-6-g21f6'/>
<meta name='robots' content='index, nofollow'/>
<link rel='stylesheet' type='text/css' href='http://cgit.freedesktop.org/cgit.css'/>
<link rel='alternate' title='Atom feed' href='http://cgit.freedesktop.org/~joonas/cairosdl/atom/Makefile?h=demos' type='application/atom+xml'/>
</head>
<body>
<div id='cgit'><table id='header'>
<tr>
<td class='logo' rowspan='2'><a href='/'><img src='http://cgit.freedesktop.org/logo.png' alt='cgit logo'/></a></td>
<td class='main'><a href='/'>index</a> : <a title='~joonas/cairosdl' href='/~joonas/cairosdl/'>~joonas/cairosdl</a></td><td class='form'><form method='get' action=''>
<select name='h' onchange='this.form.submit();'>
<option value='demos' selected='selected'>demos</option>
<option value='master'>master</option>
</select> <input type='submit' name='' value='switch'/></form></td></tr>
<tr><td class='sub'>Unnamed repository; edit this file to name it for gitweb.</td><td class='sub right'>joonas</td></tr></table>
<table class='tabs'><tr><td>
<a href='/~joonas/cairosdl/?h=demos'>summary</a><a href='/~joonas/cairosdl/refs/?h=demos'>refs</a><a href='/~joonas/cairosdl/log/?h=demos'>log</a><a class='active' href='/~joonas/cairosdl/tree/?h=demos'>tree</a><a href='/~joonas/cairosdl/commit/?h=demos'>commit</a><a href='/~joonas/cairosdl/diff/?h=demos'>diff</a></td><td class='form'><form class='right' method='get' action='/~joonas/cairosdl/log/Makefile'>
<input type='hidden' name='h' value='demos'/><select name='qt'>
<option value='grep'>log msg</option>
<option value='author'>author</option>
<option value='committer'>committer</option>
</select>
<input class='txt' type='text' size='10' name='q' value=''/>
<input type='submit' value='search'/>
</form>
</td></tr></table>
<div class='content'>path: <a href='/~joonas/cairosdl/tree/?h=demos'>root</a>/<a href='/~joonas/cairosdl/tree/Makefile?h=demos'>Makefile</a> (<a href='/~joonas/cairosdl/plain/Makefile?h=demos'>plain</a>)<br/>blob: 6b84c3d3cfd02e78b0a6db6cf2cb8af1e290d518
<table summary='blob content' class='blob'>
<tr><td class='linenumbers'><pre><a class='no' id='n1' name='n1' href='#n1'>1</a>
<a class='no' id='n2' name='n2' href='#n2'>2</a>
<a class='no' id='n3' name='n3' href='#n3'>3</a>
<a class='no' id='n4' name='n4' href='#n4'>4</a>
<a class='no' id='n5' name='n5' href='#n5'>5</a>
<a class='no' id='n6' name='n6' href='#n6'>6</a>
<a class='no' id='n7' name='n7' href='#n7'>7</a>
<a class='no' id='n8' name='n8' href='#n8'>8</a>
<a class='no' id='n9' name='n9' href='#n9'>9</a>
<a class='no' id='n10' name='n10' href='#n10'>10</a>
<a class='no' id='n11' name='n11' href='#n11'>11</a>
<a class='no' id='n12' name='n12' href='#n12'>12</a>
<a class='no' id='n13' name='n13' href='#n13'>13</a>
<a class='no' id='n14' name='n14' href='#n14'>14</a>
<a class='no' id='n15' name='n15' href='#n15'>15</a>
<a class='no' id='n16' name='n16' href='#n16'>16</a>
<a class='no' id='n17' name='n17' href='#n17'>17</a>
<a class='no' id='n18' name='n18' href='#n18'>18</a>
<a class='no' id='n19' name='n19' href='#n19'>19</a>
<a class='no' id='n20' name='n20' href='#n20'>20</a>
<a class='no' id='n21' name='n21' href='#n21'>21</a>
<a class='no' id='n22' name='n22' href='#n22'>22</a>
<a class='no' id='n23' name='n23' href='#n23'>23</a>
</pre></td>
<td class='lines'><pre><code>CFLAGS += -W -Wall -g -O3
CFLAGS += `pkg-config --cflags sdl cairo`

TARGETS=test-cairosdl fuzzy-balls sdl-clock gears

all: $(TARGETS)

fuzzy-balls: fuzzy-balls.o cairosdl.o
	$(CC) -o $@ $+ `pkg-config --libs sdl cairo`

sdl-clock: sdl-clock.o cairosdl.o
	$(CC) -o $@ $+ `pkg-config --libs sdl cairo`

gears: gears.o cairosdl.o
	$(CC) -o $@ $+ `pkg-config --libs sdl cairo`

test-cairosdl: test-cairosdl.o cairosdl.o
	$(CC) -o $@ $+ `pkg-config --libs sdl cairo`

clean:
	$(RM) $(TARGETS)
	$(RM) *.o
	$(RM) *~
</code></pre></td></tr></table>
</div> <!-- class=content -->
<div class='footer'>generated  by cgit v0.8.3-6-g21f6 at 2010-02-04 22:00:26 (GMT)</div>
</div> <!-- id=cgit -->
</body>
</html>
