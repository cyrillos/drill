#!/usr/bin/python3

import argparse
import logging
import shutil
import json
import sys
import re
import os

parser = argparse.ArgumentParser(prog='drill.py')

parser.add_argument('--conf', dest = 'conf',
                    default = 'conf/drill.json',
                    help = 'Configuration file in JSON format')

sp = parser.add_subparsers(dest = 'cmd')
for cmd in ['new']:
    spp = sp.add_parser(cmd, help = 'Add a new drill')
    spp.add_argument('--category', dest = 'category', help = 'Category',
                     required = False)
    spp.add_argument('--language', dest = 'language', help = 'Language (python3)',
                     required = False)
    spp.add_argument('--name', dest = 'name', help = 'Problem name',
                     required = True)
    spp.add_argument('--difficulty', dest = 'difficulty', help = 'Problem difficulty',
                     required = False)
    spp.add_argument('--tag', dest = 'tag', help = 'Problem tags (tag1,tag2)',
                     required = False)

logging.basicConfig(format = '%(asctime)s %(filename)s %(funcName)s %(message)s',
                    datefmt = '%m/%d/%Y %H:%M:%S', level = logging.DEBUG)

args, unknown_args = parser.parse_known_args()
if args.cmd == None:
    parser.print_help()
    sys.exit(1)

conf = []

if os.path.isfile(args.conf):
    with open(args.conf) as f:
        conf = json.load(f)
else:
    logging.error("Provide configuration")
    sys.exit(1)

if args.category == None:
    if not conf["default"]:
        logging.error("default set is not defined in config")
        sys.exit(1)
    if not conf["default"]["category"]:
        logging.error("default/category is not defined in config")
        sys.exit(1)
    args.category = conf["default"]["category"]

def process_input(args, conf):
    if not conf:
        logging.error("conf: config not present")
        return False

    if args.category not in conf:
        logging.error("conf: category '%s' missing", args.category)
        return False

    if not conf["template"]:
        logging.error("conf: 'template' missing")
        return False

    template = conf["template"]
    subconf = conf[args.category]

    if args.language:
        subconf["language"] = args.language
    elif not subconf["language"]:
        logging.error("conf: no 'language' defined for category '%s'",
                      args.category)
        return False
    if not subconf["language"] in template:
        logging.error("conf: language '%s' is not defined in 'template'",
                      subconf["language"])
        return False

    for t in template[subconf["language"]]:
        if len(t) != 3:
            logging.error("conf: wrong len in 'template'/'%s' -> %s",
                          subconf["language"], repr(t))
            return False
        if t[0] not in ["source", "text"] or \
                t[1] not in ["copy", "parse"]:
            logging.error("conf: wrong data in 'template'/'%s' -> %s",
                          subconf["language"], repr(t))
            return False

    if args.difficulty:
        if not subconf["symlinks"] or not subconf["symlinks"]["difficulty"]:
            logging.error("conf: difficulty requested but not present")
            return False

    if args.tag:
        if not subconf["symlinks"] or not subconf["symlinks"]["tag"]:
            logging.error("conf: tag requested but not present")
            return False

    return True

if args.cmd == "new":
    if not process_input(args, conf):
        sys.exit(1)

    template = conf["template"]
    subconf = conf[args.category]

    basedir = subconf["basedir"]
    if not basedir:
        logging.error("No 'basedir' found for category '%s'", args.category)
        sys.exit(1)

    if subconf["solution"]:
        solutiondir = os.path.join(basedir, subconf["solution"])
    else:
        solutiondir = basedir

    solutiondir = os.path.join(solutiondir, args.name)
    if not os.path.exists(solutiondir):
        os.makedirs(solutiondir)

    name_re = re.compile(r"\{name\}")
    source_file = None

    for tmpl in conf["template"][subconf["language"]]:
        dest = os.path.join(solutiondir, os.path.basename(tmpl[2]))
        if tmpl[0] == "source":
            source_file = dest
        if tmpl[1] == "copy":
            if not os.path.exists(dest):
                shutil.copy(tmpl[2], dest)
                logging.info("%10s: %s -> %s", tmpl[1], tmpl[2], dest)
        elif tmpl[1] == "parse":
            out = open(dest, "w")
            with open(tmpl[2], "r") as f:
                for line in f:
                    line = name_re.sub(args.name, line)
                    out.write(line)
            out.close()
            logging.info("%10s: %s -> %s", tmpl[1], tmpl[2], dest)

    if subconf["symlinks"]:
        if args.difficulty:
            path = os.path.join(basedir,
                                subconf["symlinks"]["difficulty"],
                                args.difficulty)
            if not os.path.exists(path):
                os.makedirs(path)
            dst_path = os.path.join(path, args.name)
            src_path = os.path.join("..", "..", subconf["solution"], args.name)
            os.symlink(src_path, dst_path)
            logging.info("%10s: %s -> %s", "symlink", src_path, dst_path)
        if args.tag:
            for tag in args.tag.split(","):
                path = os.path.join(basedir,
                                    subconf["symlinks"]["tag"],
                                    tag)
                if not os.path.exists(path):
                    os.makedirs(path)
                dst_path = os.path.join(path, args.name)
                src_path = os.path.join("..", "..", subconf["solution"], args.name)
                os.symlink(src_path, dst_path)
                logging.info("%10s: %s -> %s", "symlink", src_path, dst_path)
