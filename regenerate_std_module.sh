#!/bin/bash
# regenerate_std_module.sh

echo "Regenerating std.pcm module file..."

# Remove old module
rm -f std.pcm

# Generate new module with current compiler
clang++ -std=c++23 -stdlib=libc++ /usr/share/libc++/v1/std.cppm \
    -Wno-reserved-identifier -Wno-reserved-module-identifier \
    --precompile -o std.pcm

if [ $? -eq 0 ]; then
    echo "✅ Module regenerated successfully!"
    echo "📁 Location: $(pwd)/std.pcm"
    echo "📊 Size: $(du -h std.pcm | cut -f1)"
else
    echo "❌ Module generation failed!"
    exit 1
fi