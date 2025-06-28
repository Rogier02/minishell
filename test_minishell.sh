#!/bin/bash

MINISHELL=./minishell

tests=(
    "echo \"\$USER\""
    "echo '\$USER'"
    "echo \$USER"
    "echo \"Hello \$USER, your home is \$HOME\""
    "echo \"Path: \$PATH\""
    "echo 'Path: \$PATH'"
    "echo Path: \$PATH"
    "echo \"Mix\"ed'Quotes' \$USER"
    "echo ~"
    "echo ~/"
    "echo \"~\""
    "echo '~/''"
    "echo ~+ ~- ~+/foo ~-/bar"
    "echo foo~ bar~/"
    "ls *.c"
    "ls \"*\".c"
    "ls *.[ch]"
    "echo *"
    "echo \"*\""
    "echo \$USER > file.txt"
    "cat < \"\$HOME/.bashrc\" | grep \"alias\""
    "echo \"test\" | cat | wc -c"
    "echo \"foo\" > ~/testfile"
    "echo \"\""
    "echo ''"
    "echo \$UNSET_VAR"
    "echo \"A\$UNSET_VAR\"\"B\""
    "echo \"A\$USER\"\"B\""
    "echo '\$HOME'~/"
    "echo \$HOME~/"
    "echo ~notexpanded"
    "echo ~+/notexpanded"
    "echo ~-notexpanded"
    "cat <<EOF
\$USER
EOF"
    "cat <<'EOF'
\$USER
EOF"
    "cat <<EOF | grep \"\$USER\"
Hello \$USER
EOF"
    "echo \"User: \$USER, Home: \$HOME\" > ~/output.txt"
    "echo \"Files: \" *.c \"\$HOME\" | cat -n"
    "echo \"Tilde: ~, Var: \$USER, Wild: *.c\""
    "echo \"Mix\"ed'Quotes'\$USER~/"
)

expected_outputs=(
    "$USER"
    '$USER'
    "$USER"
    "Hello $USER, your home is $HOME"
    "Path: $PATH"
    'Path: $PATH'
    "Path: $PATH"
    "Mixed'Quotes' $USER"
    "$HOME"
    "$HOME/"
    "~"
    "~/"
    "$PWD $OLDPWD $PWD/foo $OLDPWD/bar"
    "foo~ bar~/"
    "$(ls *.c)"           # List of .c files, or empty if none
    "$(ls "*.c")"         # The literal string *.c if no file named *.c
    "$(ls *.[ch])"        # List of .c and .h files, or empty if none
    "$(ls *)"             # List of all non-hidden files/dirs
    "*"                   # The literal *
    ""                    # No output (output is redirected to file.txt)
    "$(cat "$HOME/.bashrc" | grep "alias")"
    "5"                   # If "test" is 5 chars including newline
    ""                    # No output (output is redirected to ~/testfile)
    ""                    # Blank line (empty string)
    ""                    # Blank line (empty string)
    ""                    # If UNSET_VAR is not set, echo prints nothing
    "AB"
    "A${USER}B"
    '$HOME'~/
    "${HOME}/"
    "~notexpanded"
    "~+/notexpanded"
    "~-notexpanded"
    "$USER"
    "\$USER"
    "Hello $USER"
    ""                    # No output (output is redirected to file)
    "$(ls *.c) $HOME"     # Output of ls *.c, then $HOME, piped to cat -n
    "Tilde: ~, Var: $USER, Wild: *.c"
    "Mixed'Quotes'${USER}${HOME}/"
)

pass=0
fail=0

for i in "${!tests[@]}"; do
    cmd="${tests[$i]}"
    expected="${expected_outputs[$i]}"
    # Capture output, strip trailing newlines for comparison
    output=$("$MINISHELL" <<EOF
$cmd
exit
EOF
)
    # Remove trailing newlines for fair comparison
    output=$(echo "$output" | sed '/^$/d')
    expected=$(echo "$expected" | sed '/^$/d')
    echo "=== Running: $cmd ==="
    echo "Output:   [$output]"
    echo "Expected: [$expected]"
    if [ "$output" = "$expected" ]; then
        echo "✅ PASS"
        ((pass++))
    else
        echo "❌ FAIL"
        ((fail++))
    fi
    echo
done

echo "Summary: $pass passed, $fail failed"