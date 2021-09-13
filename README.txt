This is the workshop repo.  If you're reading this through a webhackathon
window or a workshop SSH session, then you're probably looking at your
own private copy of the repo.

This repo contains the slides and examples used for pmem hackathons.

It is provided permanently for reference on GitHub:

	https://github.com/pmemhackathon/hackathon

The PDF files at the top level contain slides:

	slides.pdf         -- essential hackathon background

The examples are in examples/A, exmamples/B, etc.  Each example is meant
to show a heterogenous memory programming concept. There's a README.txt
file in each example directory that explains what the example is all about.

The containers used during the hackathons have all the necessary libraries
installed in them.  You can access the container directly on DockerHub
in the "pmemhackathon" area.  Here are the steps taken to install the
libraries on a Linux machine.  These steps assume you have a machine
with persistent memory installed and a recent Linux distro that supports
persistent memory.

We don't show the ipmctl and ndctl commands used to configure the
persistent memory.  These examples assume persistent memory is available
as a NUMA node on your system.  The following link
provides more details about the steps to configure persistent memory:

	https://docs.pmem.io/getting-started-guide

#
# To clone this repo, use something like the command below.
# (Examples assume cloning in your home directory, hence the "cd")
#

cd
git clone https://github.com/pmemhackathon/hackathon
