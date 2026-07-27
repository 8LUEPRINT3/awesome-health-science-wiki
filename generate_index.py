import os

wiki_dir = os.path.expanduser("~/.openclaw/workspace/wiki")
index_path = os.path.join(wiki_dir, "index.md")

with open(index_path, 'w', encoding='utf-8') as f:
    f.write("# OpenClaw Master Wiki Index\n\n")
    f.write("This index contains references to all ingested health science and development documentation.\n\n## Available Documents:\n\n")

    for file in sorted(os.listdir(wiki_dir)):
        if file.endswith('.md') and file != 'index.md':
            f.write(- [[{file[:-3]}]]\n)

print("Master index.md generated successfully!")
