#!/usr/bin/env python3

def add_custom_arguments(parser):
    parser.add_argument("-v", "--version", help="version", default="ne0")

def apply(config, args):
    version = args.version
    config['baseimg'] = f'oot/baserom_oot_{version}_uncompressed.z64'
    config['myimg'] = f'oot_{version}_uncompressed.z64'
    config['mapfile'] = f'oot/{version}/build/oot_{version}.map'
    config['makeflags'] = [f'VERSION={version}', 'KEEP_MDEBUG=1']
    config['source_directories'] = ['src', 'include', 'spec']

