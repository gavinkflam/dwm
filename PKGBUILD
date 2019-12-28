# $Id$
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.2.0
_pkgver=6.2
pkgrel=5
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2')
optdepends=('st' 'dmenu')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$_pkgver.tar.gz
	config.h
	dwm.desktop)
md5sums=('9929845ccdec4d2cc191f16210dd7f3d'
         'SKIP'
         '939f403a71b6e85261d09fc3412269ee')

prepare() {
  cd $srcdir/$pkgname-$_pkgver
  cp $srcdir/config.h config.h
}

build() {
  cd $srcdir/$pkgname-$_pkgver
  patch -p1 < ${startdir}/patches/00-dwm-noborder-6.2.diff
  patch -p1 < ${startdir}/patches/10-dwm-hide_vacant_tags-6.2.diff
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd $srcdir/$pkgname-$_pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}
