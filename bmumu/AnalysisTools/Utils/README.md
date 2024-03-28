#### Description
This folder is intended to contain useful and generic scripts.

`setup_atlas.sh`: This bash script is sourced from within other bash scripts. When doing so
the ATLAS software will be set up. Then you can call:

`setup_release`

from the same script in order to setup the release that was setup in the current directory the
last time OR the latest 21.2.X release, **only if** a release is not setup yet. You can also call:

`setup_tool TOOL TOOL_NAME`

to setup a TOOL with a TOOL_NAME, **only if** the tool has not been setup yet. For instance:

`setup_tool root root`
`setup_tool ami  pyami`

TOOL is what you call when you execute the software and TOOL_NAME is what you use when you do:

`lsetup TOOL_NAME`

These two things are not always the same.
