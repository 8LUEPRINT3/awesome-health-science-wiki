import os

raw_dir = os.path.expanduser("~/.openclaw/workspace/raw/dev")
wiki_dir = os.path.expanduser("~/.openclaw/workspace/wiki")

os.makedirs(wiki_dir, exist_ok=True)

def split_markdown_file(filepath, chunk_lines=3000):
    filename = os.path.basename(filepath)
    base_name = os.path.splitext(filename)[0]
    print(f"Processing {filename}...")
    
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()
        
    total_lines = len(lines)
    print(f"Total lines: {total_lines}")
    
    for i in range(0, total_lines, chunk_lines):
        chunk_num = (i // chunk_lines) + 1
        chunk_lines_slice = lines[i:i + chunk_lines]
        
        out_filename = f"dev_{base_name}_part{chunk_num}.md"
        out_path = os.path.join(wiki_dir, out_filename)
        
        with open(out_path, 'w', encoding='utf-8') as out_f:
            out_f.write(f"---\ntitle: {base_name} - Part {chunk_num}\nsource: {filename}\ncategory: development\n---\n\n")
            out_f.writelines(chunk_lines_slice)
            
        print(f"Created: {out_filename}")

if os.path.exists(raw_dir):
    for file in os.listdir(raw_dir):
        if file.endswith('.md'):
            split_markdown_file(os.path.join(raw_dir, file))
    print("All dev books split and saved to wiki layer successfully!")
else:
    print(f"Directory not found: {raw_dir}")
