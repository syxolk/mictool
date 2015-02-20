#include <gtest/gtest.h>
#include <cli/cli_options.h>

TEST(CLI, inputFileAndOutputFile) {
    const char *argv[] = {"mictool", "input.mpr", "--output", "output.html"};
    CLIOptions cli(4, argv);

    EXPECT_FALSE(cli.hasError());
    EXPECT_EQ(CLIOptions::OutputType::HTML, cli.format());
    EXPECT_FALSE(cli.isReadFromStdIn());
    EXPECT_FALSE(cli.isWriteToStdOut());
    EXPECT_EQ("input.mpr", cli.input());
    EXPECT_EQ("output.html", cli.output());
    EXPECT_FALSE(cli.quiet());
    EXPECT_FALSE(cli.requestedHelp());
    EXPECT_FALSE(cli.requestedVersion());
    EXPECT_EQ("mictool", cli.programName());
}

TEST(CLI, inputFileAndStdout) {
    const char *argv[] = {"./mictool", "input.mpr", "--latex"};
    CLIOptions cli(3, argv);

    EXPECT_FALSE(cli.hasError());
    EXPECT_EQ(CLIOptions::OutputType::LATEX, cli.format());
    EXPECT_FALSE(cli.isReadFromStdIn());
    EXPECT_TRUE(cli.isWriteToStdOut());
    EXPECT_EQ("input.mpr", cli.input());
    EXPECT_FALSE(cli.quiet());
    EXPECT_FALSE(cli.requestedHelp());
    EXPECT_FALSE(cli.requestedVersion());
    EXPECT_EQ("./mictool", cli.programName());
}

TEST(CLI, stdinAndOutputFile) {
    const char *argv[] = {"../mictool", "-o", "output.tex"};
    CLIOptions cli(3, argv);

    EXPECT_FALSE(cli.hasError());
    EXPECT_EQ(CLIOptions::OutputType::LATEX, cli.format());
    EXPECT_TRUE(cli.isReadFromStdIn());
    EXPECT_FALSE(cli.isWriteToStdOut());
    EXPECT_EQ("output.tex", cli.output());
    EXPECT_FALSE(cli.quiet());
    EXPECT_FALSE(cli.requestedHelp());
    EXPECT_FALSE(cli.requestedVersion());
    EXPECT_EQ("../mictool", cli.programName());
}

TEST(CLI, stdinAndStdout) {
    const char *argv[] = {"mictool", "--debug", "--quiet"};
    CLIOptions cli(3, argv);

    EXPECT_FALSE(cli.hasError());
    EXPECT_EQ(CLIOptions::OutputType::DEBUG, cli.format());
    EXPECT_TRUE(cli.isReadFromStdIn());
    EXPECT_TRUE(cli.isWriteToStdOut());
    EXPECT_TRUE(cli.quiet());
    EXPECT_FALSE(cli.requestedHelp());
    EXPECT_FALSE(cli.requestedVersion());
    EXPECT_EQ("mictool", cli.programName());
}

TEST(CLI, help) {
    const char *argv[] = {"mictool", "--help"};
    CLIOptions cli(2, argv);

    EXPECT_FALSE(cli.hasError());
    EXPECT_FALSE(cli.quiet());
    EXPECT_TRUE(cli.requestedHelp());
    EXPECT_EQ("mictool", cli.programName());
}

TEST(CLI, version) {
    const char *argv[] = {"mictool", "--version"};
    CLIOptions cli(2, argv);

    EXPECT_FALSE(cli.hasError());
    EXPECT_FALSE(cli.quiet());
    EXPECT_TRUE(cli.requestedVersion());
    EXPECT_EQ("mictool", cli.programName());
}
