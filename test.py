"""Test the take.c module."""
import os
import shlex
from unittest import TestCase
from subprocess import Popen, PIPE


class AbstractTakeTest(TestCase):
    COMMAND = NotImplemented
    EXPECTED_OUTPUT = NotImplemented

    def setUp(self):
        if os.path.exists("take"):
            os.remove("take")

        os.system("gcc take.c -o take")

    def test_leaving_empty(self):
        if self.COMMAND is NotImplemented:
            return

        if not self.EXPECTED_OUTPUT.endswith("\n"):
            self.EXPECTED_OUTPUT += "\n"

        cmd1, cmd2 = self.COMMAND.split("|")

        cmd1 = shlex.split(cmd1)
        cmd2 = shlex.split(cmd2)
        echo_process = Popen(cmd1, stdout=PIPE)
        take_process = Popen(cmd2, stdin=echo_process.stdout, stdout=PIPE)
        actual_output, err = take_process.communicate()
        self.assertEqual(actual_output, self.EXPECTED_OUTPUT)

    def tearDown(self):
        os.remove("take")

class NoChangeTest(AbstractTakeTest):
    COMMAND = "echo Hello | take :"
    EXPECTED_OUTPUT = "Hello"


class ReverseTest(AbstractTakeTest):
    COMMAND = "echo Hello | take ::-1"
    EXPECTED_OUTPUT = "olleH"


class SlicingFromTest(AbstractTakeTest):
    COMMAND = "echo Hello | take 1:"
    EXPECTED_OUTPUT = "ello"


class SlicingUntilTest(AbstractTakeTest):
    COMMAND = "echo Hello | take :4"
    EXPECTED_OUTPUT = "Hell"


class NegativeIndexTest(AbstractTakeTest):
    COMMAND = "echo Hello | take :-1"
    EXPECTED_OUTPUT = "Hell"


class BothNegativeIndexTest(AbstractTakeTest):
    COMMAND = "echo Hello | take -4:-2"
    EXPECTED_OUTPUT = "el"


class PositiveStepTest(AbstractTakeTest):
    COMMAND = "echo 123456 | take ::2"
    EXPECTED_OUTPUT = "135"


class TakeSingleCharacterTest(AbstractTakeTest):
    COMMAND = "echo Hello | take 1"
    EXPECTED_OUTPUT = "H"
