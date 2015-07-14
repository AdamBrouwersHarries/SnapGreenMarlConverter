#SnapGreenMarlConverter

A small utility for converting (in one direction only) between graph file formats. 

## Rationale

Green-Marl[1] is a leading edge graph processing toolkit from Stanford's "pervasive parallelism" laboratory. Unfortunately, Green-Marl uses a rather obtuse, badly documented binary format for describing graph files for processing. I wanted to be able to use example graphs from another of Stanford's graph analysis toolkits, SNAP[2], but was unable to due to formatting differences. This small program is designed to solve that problem, and bridge the two frameworks; It allows the user to convert a graph file in the "SNAP" format to an equivalent file in the "Green-Marl" data format. 

## Building

This program assumes you already have a built and working installation of Green-Marl on your system, as if you'd run `git clone ...` then `make compiler` and `make apps`. Essentially, all that is needed to have a working installation of `gm_graph`. Once Green-Marl is installed, first export `GM_DIR` to point to the installation of `gm_graph`. It should be located at `$(GREEN_MARL_DIRECTORY)/apps/output_cpp/gm_graph/`

## Running

The application is somewhat brittle, as it was written in a hurry to quickly convert some datafiles for benchmarking. Because of this, it only supports one invocation method:

    ./gm_convert_snap_file <input_file> <output_file>

The file specified in `<input_file>` must be a sequence of lines of the form:

    <node> <node>

Where each node is an integer. The input and output files *must* be passed as the first and second arguments (respectively) of the program; all other arguments are ignored.

## Links

[1] https://github.com/stanford-ppl/Green-Marl

[2] http://snap.stanford.edu/data/index.html