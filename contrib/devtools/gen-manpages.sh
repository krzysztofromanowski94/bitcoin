#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

DETKCOIND=${DETKCOIND:-$SRCDIR/detkcoind}
DETKCOINCLI=${DETKCOINCLI:-$SRCDIR/detkcoin-cli}
DETKCOINTX=${DETKCOINTX:-$SRCDIR/detkcoin-tx}
DETKCOINQT=${DETKCOINQT:-$SRCDIR/qt/detkcoin-qt}

[ ! -x $DETKCOIND ] && echo "$DETKCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTCVER=($($DETKCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for detkcoind if --version-string is not set,
# but has different outcomes for detkcoin-qt and detkcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$DETKCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $DETKCOIND $DETKCOINCLI $DETKCOINTX $DETKCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
