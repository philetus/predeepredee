<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='en' lang='en'>
<head>
<title>~joonas/cairosdl - Unnamed repository; edit this file to name it for gitweb.</title>
<meta name='generator' content='cgit v0.8.3-6-g21f6'/>
<meta name='robots' content='index, nofollow'/>
<link rel='stylesheet' type='text/css' href='http://cgit.freedesktop.org/cgit.css'/>
<link rel='alternate' title='Atom feed' href='http://cgit.freedesktop.org/~joonas/cairosdl/atom/test-cairosdl.c?h=demos' type='application/atom+xml'/>
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
<a href='/~joonas/cairosdl/?h=demos'>summary</a><a href='/~joonas/cairosdl/refs/?h=demos'>refs</a><a href='/~joonas/cairosdl/log/?h=demos'>log</a><a class='active' href='/~joonas/cairosdl/tree/?h=demos'>tree</a><a href='/~joonas/cairosdl/commit/?h=demos'>commit</a><a href='/~joonas/cairosdl/diff/?h=demos'>diff</a></td><td class='form'><form class='right' method='get' action='/~joonas/cairosdl/log/test-cairosdl.c'>
<input type='hidden' name='h' value='demos'/><select name='qt'>
<option value='grep'>log msg</option>
<option value='author'>author</option>
<option value='committer'>committer</option>
</select>
<input class='txt' type='text' size='10' name='q' value=''/>
<input type='submit' value='search'/>
</form>
</td></tr></table>
<div class='content'>path: <a href='/~joonas/cairosdl/tree/?h=demos'>root</a>/<a href='/~joonas/cairosdl/tree/test-cairosdl.c?h=demos'>test-cairosdl.c</a> (<a href='/~joonas/cairosdl/plain/test-cairosdl.c?h=demos'>plain</a>)<br/>blob: b18d9f924849919fc826ecb328e46f9ef4e1f738
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
<a class='no' id='n24' name='n24' href='#n24'>24</a>
<a class='no' id='n25' name='n25' href='#n25'>25</a>
<a class='no' id='n26' name='n26' href='#n26'>26</a>
<a class='no' id='n27' name='n27' href='#n27'>27</a>
<a class='no' id='n28' name='n28' href='#n28'>28</a>
<a class='no' id='n29' name='n29' href='#n29'>29</a>
<a class='no' id='n30' name='n30' href='#n30'>30</a>
<a class='no' id='n31' name='n31' href='#n31'>31</a>
<a class='no' id='n32' name='n32' href='#n32'>32</a>
<a class='no' id='n33' name='n33' href='#n33'>33</a>
<a class='no' id='n34' name='n34' href='#n34'>34</a>
<a class='no' id='n35' name='n35' href='#n35'>35</a>
<a class='no' id='n36' name='n36' href='#n36'>36</a>
<a class='no' id='n37' name='n37' href='#n37'>37</a>
<a class='no' id='n38' name='n38' href='#n38'>38</a>
<a class='no' id='n39' name='n39' href='#n39'>39</a>
<a class='no' id='n40' name='n40' href='#n40'>40</a>
<a class='no' id='n41' name='n41' href='#n41'>41</a>
<a class='no' id='n42' name='n42' href='#n42'>42</a>
<a class='no' id='n43' name='n43' href='#n43'>43</a>
<a class='no' id='n44' name='n44' href='#n44'>44</a>
<a class='no' id='n45' name='n45' href='#n45'>45</a>
<a class='no' id='n46' name='n46' href='#n46'>46</a>
<a class='no' id='n47' name='n47' href='#n47'>47</a>
<a class='no' id='n48' name='n48' href='#n48'>48</a>
<a class='no' id='n49' name='n49' href='#n49'>49</a>
<a class='no' id='n50' name='n50' href='#n50'>50</a>
<a class='no' id='n51' name='n51' href='#n51'>51</a>
<a class='no' id='n52' name='n52' href='#n52'>52</a>
<a class='no' id='n53' name='n53' href='#n53'>53</a>
<a class='no' id='n54' name='n54' href='#n54'>54</a>
<a class='no' id='n55' name='n55' href='#n55'>55</a>
<a class='no' id='n56' name='n56' href='#n56'>56</a>
<a class='no' id='n57' name='n57' href='#n57'>57</a>
<a class='no' id='n58' name='n58' href='#n58'>58</a>
<a class='no' id='n59' name='n59' href='#n59'>59</a>
<a class='no' id='n60' name='n60' href='#n60'>60</a>
<a class='no' id='n61' name='n61' href='#n61'>61</a>
<a class='no' id='n62' name='n62' href='#n62'>62</a>
<a class='no' id='n63' name='n63' href='#n63'>63</a>
<a class='no' id='n64' name='n64' href='#n64'>64</a>
<a class='no' id='n65' name='n65' href='#n65'>65</a>
<a class='no' id='n66' name='n66' href='#n66'>66</a>
<a class='no' id='n67' name='n67' href='#n67'>67</a>
<a class='no' id='n68' name='n68' href='#n68'>68</a>
<a class='no' id='n69' name='n69' href='#n69'>69</a>
<a class='no' id='n70' name='n70' href='#n70'>70</a>
<a class='no' id='n71' name='n71' href='#n71'>71</a>
<a class='no' id='n72' name='n72' href='#n72'>72</a>
<a class='no' id='n73' name='n73' href='#n73'>73</a>
<a class='no' id='n74' name='n74' href='#n74'>74</a>
<a class='no' id='n75' name='n75' href='#n75'>75</a>
<a class='no' id='n76' name='n76' href='#n76'>76</a>
<a class='no' id='n77' name='n77' href='#n77'>77</a>
<a class='no' id='n78' name='n78' href='#n78'>78</a>
<a class='no' id='n79' name='n79' href='#n79'>79</a>
<a class='no' id='n80' name='n80' href='#n80'>80</a>
<a class='no' id='n81' name='n81' href='#n81'>81</a>
<a class='no' id='n82' name='n82' href='#n82'>82</a>
<a class='no' id='n83' name='n83' href='#n83'>83</a>
<a class='no' id='n84' name='n84' href='#n84'>84</a>
<a class='no' id='n85' name='n85' href='#n85'>85</a>
<a class='no' id='n86' name='n86' href='#n86'>86</a>
<a class='no' id='n87' name='n87' href='#n87'>87</a>
<a class='no' id='n88' name='n88' href='#n88'>88</a>
<a class='no' id='n89' name='n89' href='#n89'>89</a>
<a class='no' id='n90' name='n90' href='#n90'>90</a>
<a class='no' id='n91' name='n91' href='#n91'>91</a>
<a class='no' id='n92' name='n92' href='#n92'>92</a>
<a class='no' id='n93' name='n93' href='#n93'>93</a>
<a class='no' id='n94' name='n94' href='#n94'>94</a>
<a class='no' id='n95' name='n95' href='#n95'>95</a>
<a class='no' id='n96' name='n96' href='#n96'>96</a>
<a class='no' id='n97' name='n97' href='#n97'>97</a>
<a class='no' id='n98' name='n98' href='#n98'>98</a>
<a class='no' id='n99' name='n99' href='#n99'>99</a>
<a class='no' id='n100' name='n100' href='#n100'>100</a>
<a class='no' id='n101' name='n101' href='#n101'>101</a>
<a class='no' id='n102' name='n102' href='#n102'>102</a>
<a class='no' id='n103' name='n103' href='#n103'>103</a>
<a class='no' id='n104' name='n104' href='#n104'>104</a>
<a class='no' id='n105' name='n105' href='#n105'>105</a>
<a class='no' id='n106' name='n106' href='#n106'>106</a>
<a class='no' id='n107' name='n107' href='#n107'>107</a>
<a class='no' id='n108' name='n108' href='#n108'>108</a>
<a class='no' id='n109' name='n109' href='#n109'>109</a>
<a class='no' id='n110' name='n110' href='#n110'>110</a>
<a class='no' id='n111' name='n111' href='#n111'>111</a>
<a class='no' id='n112' name='n112' href='#n112'>112</a>
<a class='no' id='n113' name='n113' href='#n113'>113</a>
<a class='no' id='n114' name='n114' href='#n114'>114</a>
<a class='no' id='n115' name='n115' href='#n115'>115</a>
<a class='no' id='n116' name='n116' href='#n116'>116</a>
<a class='no' id='n117' name='n117' href='#n117'>117</a>
<a class='no' id='n118' name='n118' href='#n118'>118</a>
<a class='no' id='n119' name='n119' href='#n119'>119</a>
</pre></td>
<td class='lines'><pre><code>#include &lt;assert.h&gt;
#include &lt;string.h&gt;
#include "cairosdl.h"

static int
sdl_surface_eq(SDL_Surface *a, SDL_Surface *b)
{
    if (a-&gt;format-&gt;BitsPerPixel != 32) return 0;
    if (a-&gt;format-&gt;BytesPerPixel != 4) return 0;
    if (SDL_MUSTLOCK(a)) return 0;
    if (SDL_MUSTLOCK(b)) return 0;

#define check_field(name) if (a-&gt;name != b-&gt;name) return 0
    check_field(format-&gt;BitsPerPixel);
    check_field(format-&gt;BytesPerPixel);
    check_field(format-&gt;Rmask);
    check_field(format-&gt;Gmask);
    check_field(format-&gt;Bmask);
    check_field(format-&gt;Amask);
    check_field(format-&gt;colorkey);
    check_field(format-&gt;alpha);
    check_field(w);
    check_field(h);

    {
        unsigned char *a_bytes = (unsigned char*)(a-&gt;pixels);
        unsigned char *b_bytes = (unsigned char*)(b-&gt;pixels);
        size_t row_size = a-&gt;format-&gt;BytesPerPixel * a-&gt;w;
        int i;
        for (i=0; i&lt;a-&gt;h; i++) {
            if (memcmp(a_bytes, b_bytes, row_size))
                return 0;
            a_bytes += a-&gt;pitch;
            b_bytes += b-&gt;pitch;
        }
        return 1;
    }
}

static SDL_Surface *
dup_sdl_surface(SDL_Surface *a)
{
    SDL_Surface *b = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                          a-&gt;w, a-&gt;h,
                                          a-&gt;format-&gt;BitsPerPixel,
                                          a-&gt;format-&gt;Rmask,
                                          a-&gt;format-&gt;Gmask,
                                          a-&gt;format-&gt;Bmask,
                                          a-&gt;format-&gt;Amask);
    unsigned char *b_bytes = (unsigned char*)(b-&gt;pixels);
    unsigned char *a_bytes = (unsigned char*)(a-&gt;pixels);
    size_t row_size = a-&gt;format-&gt;BytesPerPixel * a-&gt;w;
    int i;
    assert(! SDL_MUSTLOCK(a) );
    assert(! SDL_MUSTLOCK(b) );

    for (i=0; i&lt;a-&gt;h; i++) {
        memcpy(b_bytes, a_bytes, row_size);
        a_bytes += a-&gt;pitch;
        b_bytes += b-&gt;pitch;
    }
    return b;
}

static int
test_argb32()
{
    SDL_Surface *ref;
    SDL_Surface *sdlsurf = SDL_CreateRGBSurface(
        SDL_SWSURFACE,
        100, 100, 32,
        CAIROSDL_RMASK,
        CAIROSDL_GMASK,
        CAIROSDL_BMASK,
        CAIROSDL_AMASK);

    /* Prefilling the surface tests the mark_dirty functions. */
    SDL_FillRect(sdlsurf, NULL,
                 SDL_MapRGBA(sdlsurf-&gt;format,255,0,0,128));

    /* Make the reference image. */
    {
        SDL_Rect r;
        ref = dup_sdl_surface (sdlsurf);
        r.x = r.y = 25;
        r.w = r.h = 50;
        SDL_FillRect(ref, &amp;r,
                     SDL_MapRGBA(ref-&gt;format,255,170,0,192));
    }

    /* Draw with cairo.  cairosdl_destroy() calls the cairosdl surface
     * flush. */
    {
        cairo_t *cr = cairosdl_create(sdlsurf);

        cairo_set_source_rgba(cr, 1,1,0,0.5);
        cairo_rectangle(cr, 25,25,50,50);
        cairo_fill(cr);

        cairosdl_destroy(cr);
    }

    /* Check vs the reference. */
    {
        int ok = sdl_surface_eq(ref,sdlsurf);
        SDL_FreeSurface(ref);
        SDL_FreeSurface(sdlsurf);
        return ok;
    }
}

int
main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
    atexit(SDL_Quit);

    return test_argb32() ? 0 : 1;
}
</code></pre></td></tr></table>
</div> <!-- class=content -->
<div class='footer'>generated  by cgit v0.8.3-6-g21f6 at 2010-02-04 22:01:42 (GMT)</div>
</div> <!-- id=cgit -->
</body>
</html>
