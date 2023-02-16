<script>
    import { onMount } from "svelte";

    function saveSettings() {
        console.log(settings);

        fetch("/api/settings/picture_send/save", {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify(settings),
        })
            .then((response) => {
                console.log(response);
                return response.json();
            })
            .then((data) => {
                alert("Settings saved successfully. Restarting CAM module");
            });
    }

    let settings = { pictureUrl: "", extraJson: "", interval: 60 };

    onMount(async () => {
        const response = await fetch("/api/settings/picture_send");
        settings = await response.json();
    });
</script>

<div class="card">
    <header>User settings</header>

    <table>
        <tr>
            <th>
                <label for="picture_url">Picture send URL</label>
            </th>
            <td>
                <input
                    type="text"
                    name="picture_url"
                    bind:value={settings.pictureUrl}
                />
            </td>
        </tr>
        <tr>
            <th>
                <label for="extraJson">Additional fields JSON</label>
            </th>
            <td>
                <textarea
                    name="extraJson"
                    bind:value={settings.extraJson}
                />
            </td>
        </tr>

        <tr>
            <th>
                <label for="picture_send_interval"
                    >Send picture in minutes</label
                >
            </th>
            <td>
                <input
                    type="number"
                    name="picture_send_interval"
                    bind:value={settings.interval}
                />
            </td>
        </tr>
    </table>

    <footer class="is-right">
        <button on:click={saveSettings}> Save </button>
    </footer>
</div>
