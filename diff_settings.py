#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'oot/baserom_oot_ne0_uncompressed.z64'
    config['myimg'] = 'oot_ne0_uncompressed.z64'
    config['mapfile'] = 'oot/ne0/build/oot_ne0.map'
    config['makeflags'] = ['KEEP_MDEBUG=1']
    config['source_directories'] = ['src', 'include', 'spec']

